#include "audio.h"
#include <stdexcept>
#include <iostream>
#include <cassert>

/*!****************************************************************************
 * \brief Audio Manager control sounds
 *
 * ## Usage:
 *
 * Call initialization to setup the audio manager to create the global 
 * AudioManager instance that is required for all sounds to work.
 *
 * ## Explanation:
 * 
 * This function creates a static instance on its first call and returns a 
 * reference to it. All audio operations should be performed using this instance.
 * 
 * \return AudioManager& Reference to the singleton AudioManager.
 *****************************************************************************/
AudioManager& AudioManager::instance() {
    static AudioManager instance;
    return instance;
}


/*!****************************************************************************
 * \brief Destructor for AudioManager.
 *
 * ## Usage:
 *
 * This method is automatically triggers when the AudioManager is destroyed.
 *
 * ## Explanation:
 *
 * The destructor make sure the FMOD system is properly shut down by
 * calling shutdown(), releasing all audio resources if the user forgot to do so.
 *****************************************************************************/
AudioManager::~AudioManager() {
    shutdown();
}


/*!****************************************************************************
 * \brief Initialize the AudioManager.
 *
 * ## Usage:
 *
 * Call this method once at the start of the application to initialize the FMOD
 * audio system before any audio operations are performed.
 *
 * ## Explanation:
 *
 * This method creates and initializes the FMOD system with the specified maximum
 * number of channels. 
 *
 * \param maxChannels The maximum number of channels to allocate for audio playback.
 * \return void
 *****************************************************************************/
void AudioManager::initialize(int maxChannels) {
    // Create the main FMOD system object
    FMOD_RESULT result = FMOD::System_Create(&fmodSystem_);
    assert(result == FMOD_OK && fmodSystem_ && "FMOD system creation failed");


    // Initialize the system with a given number of channels
    result = fmodSystem_->init(maxChannels, FMOD_INIT_NORMAL, nullptr);
    assert(result == FMOD_OK && "FMOD system init failed");

    // Example: Set 3D settings if you want realistic attenuation over distance
    fmodSystem_->set3DSettings(
        1.0f,  // Doppler scale
        1.0f,  // Distance factor (1.0 = 1 meter)
        1.0f   // Rolloff scale
    );

    std::cerr << "[AudioManager] FMOD initialized with " << maxChannels << " channels.\n";
}

/*!****************************************************************************
 * \brief Update the FMOD audio system.
 *
 * ## Usage:
 *
 * Call this method once per frame (within the main loop) to allow FMOD to
 * process audio tasks.
 *
 * ## Explanation:
 *
 * This method updates the FMOD system so that the audio can be played 
 * every frame.
 *
 * \return void
 *****************************************************************************/
void AudioManager::update() {
    if (fmodSystem_) {
        fmodSystem_->update();
    }
}

/*!****************************************************************************
 * \brief Load a sound asset for later playback.
 *
 * ## Usage:
 *
 * Use this method to load a sound file into the AudioManager. This must be done
 * before attempting to play the sound.
 *
 * ## Explanation:
 *
 * This function creates a sound from the specified file path and stores it in a
 * map. The sound can be loaded as either a 3D or 2D sound, and optionally set to loop.
 *
 * \param name A unique identifier for the sound.
 * \param path The file path to the sound asset.
 * \param is3D If true, the sound is loaded as a 3D sound; otherwise as a 2D sound.
 * \param loop If true, the sound will loop over and over again.
 * \return void
 *****************************************************************************/
void AudioManager::loadSound(const std::string& name, const std::string& path, bool is3D, bool loop) {
    assert(fmodSystem_ && "FMOD system not initialized");

    // Choose either 2D or 3D mode
    FMOD_MODE mode = is3D ? (FMOD_3D | FMOD_3D_LINEARROLLOFF) : FMOD_2D;

    if (loop) {
        mode |= FMOD_LOOP_NORMAL;
    }

    FMOD::Sound* newSound = nullptr;
    FMOD_RESULT result = fmodSystem_->createSound(path.c_str(), mode, nullptr, &newSound);
    assert(result == FMOD_OK && newSound && "Failed to load sound");

    // Store the sound in the map
    sounds_[name] = newSound;
    std::cout << "[AudioManager] Loaded sound \"" << name << "\" from " << path << "\n";
}

/*!****************************************************************************
 * \brief Play a previously loaded sound.
 *
 * ## Usage:
 *
 * Call this method to play a sound that has already been loaded using loadSound().
 *
 * ## Explanation:
 *
 * This function retrieves the sound by the map location stored from loadSound()
 * and plays it using the FMOD system. If the sound is 3D, its spatial attributes 
 * are set according to the provided position.
 *
 * \param name The unique identifier of the sound to play.
 * \param x The x-coordinate of the sound's position in 3D space.
 * \param y The y-coordinate of the sound's position in 3D space.
 * \param z The z-coordinate of the sound's position in 3D space.
 * \return void
 *****************************************************************************/
void AudioManager::playSound(const std::string& name, const Vector3& position) {
    // Find the sound by its name
    auto it = sounds_.find(name);
    assert(it != sounds_.end() && "Sound not found");

    FMOD::Sound* sound = it->second;

    assert(fmodSystem_ && sound && "Cannot play sound: system or sound invalid");

    // Play the sound
    FMOD::Channel* channel = nullptr;
    FMOD_RESULT result = fmodSystem_->playSound(sound, nullptr, false, &channel);
    assert(result == FMOD_OK && "Failed to play sound");


    // If this is a 3D sound, set its position in space
    FMOD_MODE currentMode;
    sound->getMode(&currentMode);
    if ((currentMode & FMOD_3D) == FMOD_3D && channel) {
        FMOD_VECTOR pos = { position.x, position.y, position.z };
        FMOD_VECTOR vel = { 0.0f, 0.0f, 0.0f }; // velocity can be used for Doppler effect
        channel->set3DAttributes(&pos, &vel);
    }
}

/*!****************************************************************************
 * \brief Set the audio listener's position in 3D space.
 *
 * ## Usage:
 *
 * Call this method every frame (or when the listener's position changes) to update
 * the where you hear the audio. This typically reflects the camera's position.
 *
 * ## Explanation:
 *
 * This function sets the position of the primary audio listener in the FMOD system.
 *
 * \param x The x-coordinate of the listener's position.
 * \param y The y-coordinate of the listener's position.
 * \param z The z-coordinate of the listener's position.
 * \return void
 *****************************************************************************/
void AudioManager::setListenerPosition(const Vector3& position) {
    assert(fmodSystem_ && "FMOD system not initialized in setListenerPosition");

    // The orientation vectors can be adjusted based on camera property
    FMOD_VECTOR pos = { position.x, position.y, position.z };
    FMOD_VECTOR vel = { 0.0f, 0.0f, 0.0f };
    FMOD_VECTOR forward = { 0.0f, 0.0f, 1.0f };
    FMOD_VECTOR up = { 0.0f, 1.0f, 0.0f };

    // Set the listener at index 0 
    fmodSystem_->set3DListenerAttributes(0, &pos, &vel, &forward, &up);
}

/*!****************************************************************************
 * \brief Shut down the AudioManager and release all resources.
 *
 * ## Usage:
 *
 * Call this method when the application is closing to clean up all audio
 * resources and properly shut down the FMOD system.
 *
 * ## Explanation:
 *
 * This method releases all loaded sound assets and closes the FMOD system to prevent
 * memory leaks. It should be called once before the application exits.
 *
 * \return void
 *****************************************************************************/
void AudioManager::shutdown() {
    // Release all loaded sounds
    for (auto& pair : sounds_) {
        if (pair.second) {
            pair.second->release();
            pair.second = nullptr;
        }
    }
    sounds_.clear();

    // Close and release the FMOD system
    if (fmodSystem_) {
        fmodSystem_->close();
        fmodSystem_->release();
        fmodSystem_ = nullptr;
    }
    std::cout << "[AudioManager] FMOD system shut down.\n";
}
