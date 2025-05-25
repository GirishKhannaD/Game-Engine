#include "../../include/core/Tile.h"
#include "../../include/graphics/Window.h"
#include "../../include/graphics/TileTexture.h"

Tile::Tile(TileType t) : type(t) {}

void Tile::loadTile(int x, int y, float sc, std::shared_ptr<TileTexture> sharedTex) {
    position.x = x;
    position.y = y;
    texture = sharedTex;

    if (!texture) throw std::runtime_error("Tile::loadTile: texture not provided");

    sprite.setTexture(texture->getTexture());
    sprite.setScale(sc, sc);

    sf::Vector2u textSize = texture->getTexture().getSize();
    float px = static_cast<float>(x * (textSize.x * sc));
    float py = static_cast<float>(y * (textSize.y * sc));
    sprite.setPosition(px, py);
}

void Tile::draw(Window* window) {
    window->draw(sprite);
}
