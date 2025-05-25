#include "../../include/systems/Systems.h"
#include "../../include/entities/Entity.h"
#include "../../include/entities/StaticEntities.h"
#include "../../include/entities/Player.h"
#include "../../include/utils/Rectangle.h"
#include "../../include/core/Game.h"
#include "../../include/core/ServiceLocator.h"
#include <iostream>

GameplaySystem::GameplaySystem() {
    // Optional: If required, set a component mask.
    // For gameplay, we typically process collisions for static entities.
    // In this case, we don't enforce a strict mask because we want to process any entity except the player.
}

void GameplaySystem::update(Game* game, Entity* entity, float) {
    if (entity->getEntityType() == EntityType::PLAYER)
        return;

    // Get the player entity.
    std::shared_ptr<Player> player = game->getPlayer();
    if (!player)
        return;

    // Retrieve bounding boxes.
    Rectangle& playerBB = player->getBoundingBox();
    Rectangle& entityBB = entity->getBoundingBox();

    // Check if the player and this entity collide.
    if (playerBB.intersects(entityBB)) {
        std::cout << "[DEBUG] Collision detected between player and entity ID: " << entity->getID() << std::endl;
        switch (entity->getEntityType()) {
        case EntityType::POTION:
        {
            // Process collision with a Potion.
            Potion* pot = dynamic_cast<Potion*>(entity);
            if (pot) {
                int potionHealth = pot->getHealth();
                // Update the player's health.
                player->getHealthComp()->changeHealth(potionHealth);
                std::cout << "Potion collision: Restored " << potionHealth
                    << " health, new health: " << player->getHealthComp()->getHealth() << std::endl;
                // Mark the potion for deletion.
                entity->deleteEntity();
                if (player->getObserver()) {
                    player->getObserver()->onPotionCollected();
                    ServiceLocator::getAudio()->playSound("pickup");
                }
            }
            break;
        }
        case EntityType::LOG:
        {
            // Process collision with a Log.
            Log* logEntity = dynamic_cast<Log*>(entity);
            if (logEntity) {
                // Only process if the player is attacking.
                if (player->isAttacking()) {
                    int woodCollected = logEntity->getWood();
                    player->addWood(woodCollected);
                    std::cout << "Log collision: Collected " << woodCollected
                        << " wood, total wood: " << player->getWood() << std::endl;
                    // Mark the log for deletion.
                    entity->deleteEntity();
                }
            }
            break;
        }
        default:
            break;
        }
    }
}
