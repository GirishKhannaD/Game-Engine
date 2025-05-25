#include "../../include/systems/Systems.h"
#include "../../include/components/VelocityComponent.h"
#include "../../include/components/PositionComponent.h"
#include "../../include/entities/Entity.h"
#include <stdexcept>

MovementSystem::MovementSystem() {
    componentMask.turnOnBit(static_cast<unsigned int>(ComponentID::VELOCITY));
    componentMask.turnOnBit(static_cast<unsigned int>(ComponentID::POSITION));
}

void MovementSystem::update(Game* game, Entity* entity, float elapsed) {
    auto velComp = std::dynamic_pointer_cast<VelocityComponent>(entity->getComponent(ComponentID::VELOCITY));
    auto posComp = std::dynamic_pointer_cast<PositionComponent>(entity->getComponent(ComponentID::POSITION));

    if (!velComp || !posComp) {
        throw std::runtime_error("MovementSystem: missing Velocity or Position component");
    }

    velComp->update(*posComp, elapsed);
}
