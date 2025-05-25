#pragma once
#include <SFML/System/Vector2.hpp>
#include "Components.h"
class PositionComponent;

class VelocityComponent: public Component{
public:
    ComponentID getID() const override {
        return ComponentID::VELOCITY;
    }

    VelocityComponent(float spd = 1.f);
    void setVelocity(float x, float y);
    const sf::Vector2f& getVelocity() const;
    // Update the PositionComponent based on velocity * speed * elapsed.
    void update(PositionComponent& posComp, float elapsed);
private:
    sf::Vector2f velocity;
    float speed;
};
