#include "../../include/components/InputComponent.h"
#include "../../include/core/Game.h"
#include "../../include/core/InputHandler.h"
#include "../../include/entities/Player.h"
#include <iostream>

PlayerInputComponent::PlayerInputComponent()
{
    inputHandler = std::make_unique<PlayerInputHandler>();
}

void PlayerInputComponent::update(Game& game)
{
    auto player = game.getPlayer();
    if (!player) { return; }

    // Reset player's velocity via its VelocityComponent.
    auto velComp = player->getVelocityComp();
    if (velComp) {
        velComp->setVelocity(0.f, 0.f);
    }

    // Retrieve commands from the PlayerInputHandler and execute them.
    auto& commands = inputHandler->handleInput();
    for (auto& cmd : commands) {
        cmd->execute(game);
    }
}
