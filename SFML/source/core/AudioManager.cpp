#include "../../include/core/AudioManager.h"
#include <iostream>

void AudioManager::loadSound(const std::string& name, const std::string& filepath) {
    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile(filepath)) {
        std::cerr << "[AudioManager] Failed to load: " << filepath << "\n";
        return;
    }
    buffers[name] = buffer;
    sounds[name].setBuffer(buffers[name]);
}

void AudioManager::playSound(const std::string& name) {
    if (sounds.count(name)) {
        sounds[name].play();
    }
}
