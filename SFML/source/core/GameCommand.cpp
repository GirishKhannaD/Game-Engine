#include "../../include/core/Command.h"
#include "../../include/core/Game.h"
#include "../../include/entities/Player.h"
#include <SFML/Window/Keyboard.hpp>

// Example PauseCommand
void PauseCommand::execute(Game& game)
{
    game.togglePause();
}

// Movement commands
void MoveRightCommand::execute(Game& game)
{
    auto player = game.getPlayer();
    if (!player) return;

    // Retrieve the velocity component
    auto vcomp = player->getVelocityComp();
    if (!vcomp) return;

    // Set velocity.x = +150, keep old velocity.y
    sf::Vector2f oldVel = vcomp->getVelocity();
    vcomp->setVelocity(150.f, oldVel.y);
}

void MoveLeftCommand::execute(Game& game)
{
    auto player = game.getPlayer();
    if (!player) return;

    auto vcomp = player->getVelocityComp();
    if (!vcomp) return;

    // Set velocity.x = -150, keep old velocity.y
    sf::Vector2f oldVel = vcomp->getVelocity();
    vcomp->setVelocity(-150.f, oldVel.y);
}

void MoveUpCommand::execute(Game& game)
{
    auto player = game.getPlayer();
    if (!player) return;

    auto vcomp = player->getVelocityComp();
    if (!vcomp) return;

    // Set velocity.y = -150, keep old velocity.x
    sf::Vector2f oldVel = vcomp->getVelocity();
    vcomp->setVelocity(oldVel.x, -150.f);
}

void MoveDownCommand::execute(Game& game)
{
    auto player = game.getPlayer();
    if (!player) return;

    auto vcomp = player->getVelocityComp();
    if (!vcomp) return;

    // Set velocity.y = +150, keep old velocity.x
    sf::Vector2f oldVel = vcomp->getVelocity();
    vcomp->setVelocity(oldVel.x, 150.f);
}

// Attack / Shout
void AttackCommand::execute(Game& game)
{
    auto player = game.getPlayer();
    if (player && !player->isAttacking()) {
        player->setAttacking(true);
    }
}

void ShoutCommand::execute(Game& game)
{
    auto player = game.getPlayer();
    if (player && !player->isShouting()) {
        player->setShouting(true);
    }
}
