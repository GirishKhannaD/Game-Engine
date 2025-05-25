#pragma once
#include "../../include/graphics/Window.h"
#include "Components.h"

class Entity;
class Game;
class SpriteSheet;

class GraphicsComponent: public Component {
public:
    ComponentID getID() const override {
        return ComponentID::GRAPHICS;
    }

    virtual ~GraphicsComponent() = default;
    virtual void update(Entity* entity, float elapsed) = 0;
    virtual void draw(Window* window) = 0;
    // Added so that the Player can access the underlying SpriteSheet if needed.
    virtual SpriteSheet* getSpriteSheet() { return nullptr; }
};
