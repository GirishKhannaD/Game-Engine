#include "../../include/systems/Systems.h"
#include "../../include/components/ColliderComponent.h"
#include "../../include/entities/Entity.h"
#include "../../include/core/Game.h"
#include <stdexcept>

ColliderSystem::ColliderSystem() {
    // Set the required component bit for ColliderComponent.
    componentMask.turnOnBit(static_cast<unsigned int>(ComponentID::COLLIDER));
}

void ColliderSystem::update(Game* game, Entity* entity, float elapsed) {
    // Retrieve the ColliderComponent from the entity using getComponent()
    auto comp = entity->getComponent(ComponentID::COLLIDER);
    auto colliderComp = std::dynamic_pointer_cast<ColliderComponent>(comp);

    if (!colliderComp) {
        throw std::runtime_error("ColliderSystem: Entity lacks a ColliderComponent");
    }

    // Determine the entity's position
    sf::Vector2f pos = entity->getPosition();

    // Determine the size for the collider update.
    // For simplicity, use the entity's texture size and convert it to a sf::Vector2f.
    sf::Vector2i texSizeInt = entity->getTextureSize();
    sf::Vector2f size(static_cast<float>(texSizeInt.x), static_cast<float>(texSizeInt.y));

    // Update the collider component bounding box using the entity's position and calculated size.
    colliderComp->update(pos, size);
}
