#pragma once
#include "Components.h"

class Entity;
class Game;

class LogicComponent: public Component {
public:
    ComponentID getID() const override {
        return ComponentID::LOGIC;
    }

    virtual ~LogicComponent() = default;
    virtual void update(Entity* entity, Game* game, float elapsed) = 0;
};
