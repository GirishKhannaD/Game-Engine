#pragma once
#include "LogicComponent.h"

class PlayerStateComponent : public LogicComponent {
public:
    PlayerStateComponent();
    ~PlayerStateComponent() override = default;
    void update(Entity* entity, Game* game, float elapsed) override;
};

