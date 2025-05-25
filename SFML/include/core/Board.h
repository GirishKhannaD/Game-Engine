#pragma once
#include <vector>
#include <unordered_map>
#include <memory>
#include "Tile.h"
#include "../../include/graphics/TileTexture.h"

class Board {
public:
    Board(size_t width, size_t height);
    ~Board();

    void addTile(int x, int y, float scale, TileType type, const std::string& textureFile);
    void draw(class Window* wnd);
    bool inBounds(int x, int y) const;

private:
    size_t width, height;
    std::vector<Tile*> grid;

    // Flyweight storage
    std::unordered_map<std::string, std::shared_ptr<TileTexture>> textureMap;
};
