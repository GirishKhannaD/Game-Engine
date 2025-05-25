#include "../../include/entities/Player.h"
#include "../../include/graphics/AnimBase.h"
#include "../../include/entities/Fire.h"
#include "../../include/core/Game.h"
#include <iostream>
#include "../../include/core/Command.h"
#include "../../include/components/InputComponent.h"
#include "../../include/core/ServiceLocator.h"
#include "../../include/entities/StaticEntities.h"

const float Player::playerSpeed = 1.f;        
const float Player::fireSpeed = 1.f;            
const float Player::shootingCost = 1.f;
const float Player::shootCooldownTime = 0.5f;


Player::Player()
    : Entity(EntityType::PLAYER),
    attacking(false),
    shouting(false),
    wood(0),
    shootCooldown(0)
{
    // Initialize player's velocity component with playerSpeed.
    velocity = std::make_shared<VelocityComponent>(playerSpeed);
    addComponent(velocity);

    input = std::make_shared<PlayerInputComponent>();
    addComponent(input);

    // Create the HealthComponent using startingHealth and maxHealth.
    healthComp = std::make_shared<HealthComponent>(startingHealth, maxHealth);
    addComponent(healthComp);
}

Player::~Player() {}

void Player::init(const std::string& textureFile, float scale) {
    Entity::init(textureFile, scale);
}

void Player::initSpriteSheet(const std::string& spriteSheetFile) {
    Entity::initSpriteSheet(spriteSheetFile);
}

void Player::setObserver(std::shared_ptr<Observer> obs) {
    observer = obs;
}

std::shared_ptr<Observer> Player::getObserver() const {
    return observer;
}

void Player::update(Game* game, float elapsed) {
    // Update the player's position via the VelocityComponent.
    if (velocity) {
        velocity->update(*getPositionComp(), elapsed);
    }

    // Update animations based on current movement.
    sf::Vector2f vel = velocity->getVelocity();
    if (attacking ) {
        // Play the "Attack" animation
            spriteSheet.setAnimation("Attack", true, false);
    }
    else if (shouting) {
        // Play the "Shout" animation
        spriteSheet.setAnimation("Shout", true, false);
    }
    else {
        if (vel.x > 0) {
            spriteSheet.setAnimation("Walk", true, true);
            spriteSheet.setSpriteDirection(Direction::Right);
        }
        else if (vel.x < 0) {
            spriteSheet.setAnimation("Walk", true, true);
            spriteSheet.setSpriteDirection(Direction::Left);
        }
        else if (vel.y < 0) {
            spriteSheet.setAnimation("Walk", true, true);
        }
        else if (vel.y > 0) {
            spriteSheet.setAnimation("Walk", true, true);
        }
        else {
            spriteSheet.setAnimation("Idle", true, true);
        }
    }

    // Decrement shoot cooldown.
    if (shootCooldown > 0) {
        shootCooldown -= elapsed;
    }
    // Fire spawning: if the player is shouting, the current animation is "in action", enough wood is available,
    // and the cooldown has elapsed.
    if (shouting &&
        spriteSheet.getCurrentAnim() && spriteSheet.getCurrentAnim()->isInAction() &&
        wood >= static_cast<int>(shootingCost) && shootCooldown <= 0) {
        auto fire = createFire();
        game->addEntity(fire);
        ServiceLocator::getAudio()->playSound("fire");
        wood -= static_cast<int>(shootingCost);
        shootCooldown = shootCooldownTime;
        // Reset the shouting flag so that fire is spawned only once per key press.
        shouting = false;

        if (observer) {
            observer->onShoutPerformed();
        }
    }

    // Reset attack/shout flags when the animation is finished.
    if (spriteSheet.getCurrentAnim() && !spriteSheet.getCurrentAnim()->isPlaying()) {
        attacking = false;
        shouting = false;
    }

    if (attacking &&
        spriteSheet.getCurrentAnim() &&
        spriteSheet.getCurrentAnim()->isInAction()) {
        ServiceLocator::getAudio()->playSound("axe");
    }

    // Call the base Entity update to update bounding box and sprite position.
    Entity::update(game, elapsed);
}

void Player::draw(Window* window) {
    Entity::draw(window);
}

void Player::handleInput(Game& game) {
    if (input) {
        input->update(game);
    }
}

void Player::addWood(int w) {
    wood += w;
    if (wood > maxWood) { wood = maxWood; }
    if (wood < 0) { wood = 0; }
}

std::shared_ptr<Fire> Player::createFire() const {
    auto fireEntity = std::make_shared<Fire>();
    sf::Vector2f pos = getPosition();
    pos.x += getTextureSize().x * 0.5f;
    pos.y += getTextureSize().y * 0.5f;
    fireEntity->init("img/fire.png", 1.f);
    fireEntity->setPosition(pos.x, pos.y);
    // Set fire velocity based on player's facing direction.
    auto fireVel = fireEntity->getVelocityComp();
    if (fireVel) {
        if (spriteSheet.getSpriteDirection() == Direction::Left)
            fireVel->setVelocity(-fireSpeed, 0.f);
        else
            fireVel->setVelocity(fireSpeed, 0.f);
    }
    return fireEntity;
}

void Player::positionSprite(int row, int col, int spriteWH, float tileScale) {
    sf::Vector2f scaleV2f = getSpriteScale();
    sf::Vector2i texSize = getTextureSize();
    float x = col * spriteWH * tileScale;
    float y = row * spriteWH * tileScale;
    float spriteSizeY = scaleV2f.y * texSize.y;
    float cntrFactorY = (spriteWH * tileScale - spriteSizeY);
    float cntrFactorX = cntrFactorY * 0.5f;
    setPosition(x + cntrFactorX, y + cntrFactorY);
    if (velocity) {
        velocity->setVelocity(0.f, 0.f);
    }
}

void Player::handlePotionCollision(Entity* potion) { 
    auto pot = dynamic_cast<Potion*>(potion);
    if (pot && healthComp) {
        int potionHealth = pot->getHealth();
        healthComp->changeHealth(potionHealth);
        std::cout << "Potion restores: " << potionHealth
            << ", Player Health: " << healthComp->getHealth() << std::endl;
        if (observer) observer->onPotionCollected();
        ServiceLocator::getAudio()->playSound("pickup");
        potion->deleteEntity();
    }
}

void Player::handleLogCollision(Entity* log) {
    if (!isAttacking() || !spriteSheet.getCurrentAnim() || !spriteSheet.getCurrentAnim()->isInAction())
        return;

    auto logObj = dynamic_cast<Log*>(log);
    if (logObj) {
        int logWood = logObj->getWood();
        addWood(logWood);
        std::cout << "Wood collected: " << logWood
            << ", Total Wood: " << getWood() << std::endl;
        log->deleteEntity();
    }
}

