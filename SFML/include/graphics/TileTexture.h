#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class TileTexture {
public:
    bool loadFromFile(const std::string& file) {
        return texture.loadFromFile(file);
    }

    const sf::Texture& getTexture() const { return texture; }

private:
    sf::Texture texture;
};

