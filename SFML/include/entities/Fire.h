#pragma once
#include "Entity.h"
#include <memory>
#include "../../include/components/TTLComponent.h"
#include "../../include/components/VelocityComponent.h"

class Fire : public Entity {
public:
    // The starting time-to-live for a Fire object (in frames).
    const int startTimeToLive = 150;

    Fire();
    ~Fire();

    // Update the Fire: update its position via its VelocityComponent, update the TTL,
    // and mark for deletion if its TTL reaches 0.
    void update(Game* game, float elapsed = 1.0f) override;

    // Return the current TTL value.
    int getTTL() const { return ttl ? ttl->getTTL() : 0; }

    // Return the shared pointer to the VelocityComponent.
    std::shared_ptr<VelocityComponent> getVelocityComp() const { return velocity; }

    std::shared_ptr<TTLComponent> getTTLComponent() const override;

private:
    // The TTL component handles the time-to-live logic.
    std::shared_ptr<TTLComponent> ttl;

    // The Velocity component handles movement.
    std::shared_ptr<VelocityComponent> velocity;
};
