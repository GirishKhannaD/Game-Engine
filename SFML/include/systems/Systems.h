#pragma once
#include "../../include/core/Game.h"
#include "../../include/entities/Entity.h"
#include "../../include/utils/Bitmask.h"

// Abstract base class for all systems
class System {
protected:
    Bitmask componentMask; // Bitmask indicating which components this system operates on

public:
    virtual ~System() = default;

    // Pure virtual update function
    virtual void update(Game* game, Entity* entity, float elapsed) = 0;

    // Check if an entity matches the system's required component mask
    bool validate(Entity* entity) const {
        if (componentMask.getMask() == 0) return false;
        return entity->hasComponent(componentMask);
    }
};

class TTLSystem : public System {
public:
    TTLSystem();
    void update(Game* game, Entity* entity, float elapsed) override;
};

class InputSystem : public System {
public:
    InputSystem(); 
    void update(Game* game, Entity* entity, float elapsed) override;
};

class MovementSystem : public System {
public:
    MovementSystem();
    void update(Game* game, Entity* entity, float elapsed) override;
};

class GraphicsSystem : public System {
public:
    GraphicsSystem();
    void update(Game* game, Entity* entity, float elapsed) override;
};

class ColliderSystem : public System {
public:
    ColliderSystem();
    void update(Game* game, Entity* entity, float elapsed) override;
};

class GameplaySystem : public System {
public:
    GameplaySystem();
    void update(Game* game, Entity* entity, float elapsed) override;
};

class PrintDebugSystem: public System{
public:
    PrintDebugSystem();
    void update(Game* game, Entity* entity, float elapsed) override;
};