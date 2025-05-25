#pragma once
#include <SFML/System/Vector2.hpp>
#include "Components.h"

class PositionComponent: public Component{
public:
    ComponentID getID() const override {
        return ComponentID::POSITION;
    }

    PositionComponent() : position(0.f, 0.f) {}
    PositionComponent(float x, float y) : position(x, y) {}

    const sf::Vector2f& getPosition() const { return position; }
    void setPosition(float x, float y) { position = sf::Vector2f(x, y); }
    void setPosition(const sf::Vector2f& pos) { position = pos; }

private:
    sf::Vector2f position;
};
