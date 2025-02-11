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
#pragma once
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
    static AudioManager& instance();
    void init(int maxChannels = 512);
    void update();
    void loadSound(const std::string& name, const std::string& path, bool is3D = false, bool loop = false);
    void playSound(const std::string& name, float x = 0.0f, float y = 0.0f, float z = 0.0f);
    void setListenerPosition(float x, float y, float z);
    void shutdown();

private:
    AudioManager() = default;
    ~AudioManager();

    AudioManager(const AudioManager&) = delete;
    AudioManager& operator=(const AudioManager&) = delete;
    FMOD::System* fmodSystem_ = nullptr;
    std::unordered_map<std::string, FMOD::Sound*> sounds_;
};

#endif // AUDIO_H
