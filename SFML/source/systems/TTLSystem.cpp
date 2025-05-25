#include "../../include/systems/Systems.h"
#include "../../include/components/TTLComponent.h"
#include "../../include/entities/Entity.h"
#include <stdexcept>

TTLSystem::TTLSystem() {
    componentMask.turnOnBit(static_cast<unsigned int>(ComponentID::TTL));
}

void TTLSystem::update(Game* game, Entity* entity, float) {
    auto ttlComp = entity->getTTLComponent();
    if (!ttlComp) {
        throw std::runtime_error("TTLSystem: Entity lacks TTLComponent");
    }

    ttlComp->update();

    if (ttlComp->getTTL() <= 0) {
        entity->deleteEntity();
    }
}
