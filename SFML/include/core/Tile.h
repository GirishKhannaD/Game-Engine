#pragma once
#include "../../include/utils/Vector2.h"
#include <SFML/Graphics.hpp>
#include <memory>

class TileTexture;

enum class TileType { CORRIDOR, WALL };

class Tile {
public:
    Tile(TileType t);

    void loadTile(int x, int y, float scale, std::shared_ptr<TileTexture> sharedTex);
    void draw(class Window* window);
    TileType getType() const { return type; }

private:
    TileType type;
    sf::Vector2i position;
    sf::Sprite sprite;
    std::shared_ptr<TileTexture> texture; //Flyweight: shared texture
};
