#include "../../include/entities/Fire.h"
#include "../../include/components/TTLComponent.h"
#include "../../include/components/VelocityComponent.h"
#include "../../include/core/Game.h"
#include <iostream>

Fire::Fire() : Entity(EntityType::FIRE) {
    // Initialize the TTL component using the defined startTimeToLive.
    ttl = std::make_shared<TTLComponent>(startTimeToLive);
    addComponent(ttl);

    // Initialize the Velocity component for Fire with a speed of 200.f.
    velocity = std::make_shared<VelocityComponent>(200.f);
    addComponent(velocity);

}


Fire::~Fire() {}

std::shared_ptr<TTLComponent> Fire::getTTLComponent() const {
    return ttl;
}

void Fire::update(Game* game, float elapsed) {
    
    if (velocity) {
        velocity->update(*getPositionComp(), elapsed);
    }
    Entity::update(game, elapsed);
}
