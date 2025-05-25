#pragma once
#pragma once
#include <SFML/Audio.hpp>
#include <map>
#include <string>
#include <memory>

class AudioManager {
public:
    void loadSound(const std::string& name, const std::string& filepath);
    void playSound(const std::string& name);

private:
    std::map<std::string, sf::SoundBuffer> buffers;
    std::map<std::string, sf::Sound> sounds;
};
