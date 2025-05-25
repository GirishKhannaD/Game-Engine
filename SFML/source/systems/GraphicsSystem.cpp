#include "../../include/systems/Systems.h"
#include "../../include/components/GraphicsComponent.h"
#include "../../include/entities/Entity.h"
#include "../../include/graphics/Window.h"
#include "../../include/core/Game.h"
#include <stdexcept>

GraphicsSystem::GraphicsSystem() {
    // Set the system's component mask to require a Graphics component.
    componentMask.turnOnBit(static_cast<unsigned int>(ComponentID::GRAPHICS));
}

void GraphicsSystem::update(Game* game, Entity* entity, float elapsed) {
    // Retrieve the GraphicsComponent from the entity.
    auto comp = entity->getComponent(ComponentID::GRAPHICS);
    auto graphicsComp = std::dynamic_pointer_cast<GraphicsComponent>(comp);

    if (!graphicsComp) {
        throw std::runtime_error("GraphicsSystem: Entity lacks a GraphicsComponent");
    }

    // Update the graphics component (e.g., update animations)
    graphicsComp->update(entity, elapsed);

    // Draw the graphics component on the game's window.
    graphicsComp->draw(game->getWindow());
}
