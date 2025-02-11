/*!****************************************************************************
 * \file   Audio.h
 * \author Lixiao Kuang (li.kuang@digipen.edu)
 * \par    **DigiPen Email**
 *    li.kuang@digipen.edu
 * \par    **Course**
 *    GAM541
 * \date   01-26-2025
 * \brief  File to handle audio output
 * 
 *****************************************************************************/
#ifndef AUDIO_H
#define AUDIO_H

#include <string>
#include <unordered_map>
#include <fmod/fmod.hpp>


/*!****************************************************************************
 * \brief A singleton class to manage all audio functionality using FMOD.
 * 
 * ## Usage
 * 
 * Call AudioManager::instance().init(); once at startup, then:
 * - loadSound() for each sound you want to use
 * example: AudioManager::instance().loadSound("pew", "/media/pew.mp3", true); //true if sound in 3D, false if in 2D(mono sound) for music n etc
 * 
 * - playSound() to play them
 * example: AudioManager::instance().playSound("pew", 0, 0, 0);
 * 
 * - update() // Be sure to call AudioManager::instance().update(); every frame to update the sound
 * 
 * - shutdown() // Be sure to shut down by AudioManager::instance().shutdown(); before ending the game
 * 
 *****************************************************************************/

class AudioManager {
public:

    /** creates A single, global instance of the AudioManager.*/
    static AudioManager& instance();

    /** Initialize FMOD and set default 3D settings, maxChannels The maximum number of channels FMOD can play simultaneously.*/
    void init(int maxChannels = 512);

    /** Update FMOD's internal state each frame, should be called once per game loop iteration.*/
    void update();

    /** Load a sound into the manager's cache, the string key used to identify this sound later (ex: "pew"),
    * the path the file path to the sound (ex: "media/pew.mp3") and is3D to tell Whether this sound is 3D 
    * (positional audio) or 2D (mono audio).   
    */
    void loadSound(const std::string& name, const std::string& path, bool is3D = false, bool loop = false);

    /**
     * Play a previously loaded sound, name The string key for the sound (must match what you used in loadSound(),
     * x, y, z The position of the sound in 3D space (only matters if is3D was true).
     */
    void playSound(const std::string& name, float x = 0.0f, float y = 0.0f, float z = 0.0f);

    /** Set the listener's position in the world, the x, y, z 3D coordinates of the listener (player/camera). */
    void setListenerPosition(float x, float y, float z);

    /** Shut down FMOD and free all loaded sounds. */
    void shutdown();

private:
    // Private constructor/destructor to enforce singleton pattern
    AudioManager() = default;
    ~AudioManager();

    // Disallow copy and assign
    AudioManager(const AudioManager&) = delete;
    AudioManager& operator=(const AudioManager&) = delete;

    // Internal pointer to FMOD system
    FMOD::System* fmodSystem_ = nullptr;
    // Stores pointers to loaded sounds, accessible by a string key
    std::unordered_map<std::string, FMOD::Sound*> sounds_;
};

#endif // AUDIO_H
