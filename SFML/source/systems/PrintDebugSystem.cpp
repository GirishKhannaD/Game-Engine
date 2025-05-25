#include "../../include/systems/Systems.h"
#include "../../include/components/ColliderComponent.h"
#include "../../include/entities/Entity.h"
#include "../../include/graphics/Window.h"
#include <stdexcept>

PrintDebugSystem::PrintDebugSystem() {
    // Set the bitmask for this system so it only operates on entities with a ColliderComponent.
    componentMask.turnOnBit(static_cast<unsigned int>(ComponentID::COLLIDER));
}

void PrintDebugSystem::update(Game* game, Entity* entity, float ) {
    // Retrieve the ColliderComponent from the entity.
    auto comp = entity->getComponent(ComponentID::COLLIDER);
    auto colliderComp = std::dynamic_pointer_cast<ColliderComponent>(comp);

    if (!colliderComp) {
        // Throw an exception if the entity does not have a ColliderComponent.
        throw std::runtime_error("PrintDebugSystem: Entity lacks a ColliderComponent");
    }

    // Retrieve a reference to the SFML drawable rectangle from the ColliderComponent's bounding box.
    //auto& debugRect = colliderComp->getBoundingBox().getDrawableRect();
    auto boundingBox = colliderComp->getBoundingBox();
    auto& debugRect = boundingBox.getDrawableRect();

    // Draw the debug rectangle on the window.
    game->getWindow()->draw(debugRect);
}