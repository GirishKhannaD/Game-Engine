#include "../../include/Components/VelocityComponent.h"
#include "../../include/Components/PositionComponent.h"

VelocityComponent::VelocityComponent(float spd)
    : velocity(0.f, 0.f), speed(spd)
{
}

void VelocityComponent::setVelocity(float x, float y) {
    velocity.x = x; velocity.y = y;
}

const sf::Vector2f& VelocityComponent::getVelocity() const {
    return velocity;
}

void VelocityComponent::update(PositionComponent& posComp, float elapsed) {
    sf::Vector2f pos = posComp.getPosition();
    pos.x += velocity.x * speed * elapsed;
    pos.y += velocity.y * speed * elapsed;
    posComp.setPosition(pos);
}
