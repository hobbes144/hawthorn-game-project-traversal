#include "audio.h"
#include <stdexcept>
#include <iostream>

/** Create the singleton instance */
AudioManager& AudioManager::instance() {
    static AudioManager instance;
    return instance;
}


/** Destructor */
AudioManager::~AudioManager() {
    // Ensure we clean up if user forgot to call shutdown()
    shutdown();
}


/** initialization */
void AudioManager::init(int maxChannels) {
    // Create the main FMOD system object
    FMOD_RESULT result = FMOD::System_Create(&fmodSystem_);
    if (result != FMOD_OK || !fmodSystem_) {
        throw std::runtime_error("FMOD system creation failed");
    }

    // Initialize the system with a given number of channels
    result = fmodSystem_->init(maxChannels, FMOD_INIT_NORMAL, nullptr);
    if (result != FMOD_OK) {
        throw std::runtime_error("FMOD system init failed");
    }

    // Example: Set 3D settings if you want realistic attenuation over distance
    fmodSystem_->set3DSettings(
        1.0f,  // Doppler scale
        1.0f,  // Distance factor (1.0 = 1 meter)
        1.0f   // Rolloff scale
    );

    std::cout << "[AudioManager] FMOD initialized with " << maxChannels << " channels.\n";
}

/** Update, Must be called once per frame so FMOD can process 3D audio, streaming, etc. */
void AudioManager::update() {
    if (fmodSystem_) {
        fmodSystem_->update();
    }
}

/* LoadSound so it can be played later*/
void AudioManager::loadSound(const std::string& name, const std::string& path, bool is3D, bool loop) {
    if (!fmodSystem_) {
        std::cerr << "[AudioManager] Error: FMOD system not initialized.\n";
        return;
    }

    // Choose either 2D or 3D mode
    FMOD_MODE mode = is3D ? (FMOD_3D | FMOD_3D_LINEARROLLOFF) : FMOD_2D;

    if (loop) {
        mode |= FMOD_LOOP_NORMAL;
    }

    FMOD::Sound* newSound = nullptr;
    FMOD_RESULT result = fmodSystem_->createSound(path.c_str(), mode, nullptr, &newSound);
    if (result != FMOD_OK || !newSound) {
        std::cerr << "[AudioManager] Failed to load sound: " << path << std::endl;
        return;
    }

    // Store the sound in the map
    sounds_[name] = newSound;
    std::cout << "[AudioManager] Loaded sound \"" << name << "\" from " << path << "\n";
}

/** Play the sound stored in loadsound() */
void AudioManager::playSound(const std::string& name, float x, float y, float z) {
    // Find the sound by its name
    auto it = sounds_.find(name);
    if (it == sounds_.end()) {
        std::cerr << "[AudioManager] Sound not found: " << name << std::endl;
        return;
    }
    FMOD::Sound* sound = it->second;

    if (!fmodSystem_ || !sound) {
        std::cerr << "[AudioManager] Cannot play sound. System or sound invalid.\n";
        return;
    }

    // Play the sound
    FMOD::Channel* channel = nullptr;
    FMOD_RESULT result = fmodSystem_->playSound(sound, nullptr, false, &channel);
    if (result != FMOD_OK) {
        std::cerr << "[AudioManager] Failed to play sound: " << name << std::endl;
        return;
    }

    // If this is a 3D sound, set its position in space
    FMOD_MODE currentMode;
    sound->getMode(&currentMode);
    if ((currentMode & FMOD_3D) == FMOD_3D && channel) {
        FMOD_VECTOR pos = { x, y, z };
        FMOD_VECTOR vel = { 0.0f, 0.0f, 0.0f }; // velocity can be used for Doppler effect
        channel->set3DAttributes(&pos, &vel);
    }
}

/** setListenerPosition() */
void AudioManager::setListenerPosition(float x, float y, float z) {
    if (!fmodSystem_) return;

    // The orientation vectors can be adjusted based on camera property
    FMOD_VECTOR position = { x, y, z };
    FMOD_VECTOR velocity = { 0.0f, 0.0f, 0.0f };
    FMOD_VECTOR forward = { 0.0f, 0.0f, 1.0f };
    FMOD_VECTOR up = { 0.0f, 1.0f, 0.0f };

    // Set the listener at index 0 
    fmodSystem_->set3DListenerAttributes(0, &position, &velocity, &forward, &up);
}

/** shutdown() */
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
