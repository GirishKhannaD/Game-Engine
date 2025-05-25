#pragma once
#include "Entity.h"
#include "../../include/components/HealthComponent.h"
#include "../../include/components/VelocityComponent.h"
#include <memory>
#include "../../include/utils/Observer.h"

class InputComponent;
class Fire;

class Player : public Entity {
public:
    static const int startingHealth = 80;
    static const int maxHealth = 100;
    static const int maxWood = 999;
    static const float playerSpeed;
    static const float fireSpeed;
    static const float shootingCost;
    static const float shootCooldownTime;

    Player();
    ~Player() override;

    void handlePotionCollision(Entity* potion);
    void handleLogCollision(Entity* log);

    // Overridden initialization functions.
    void init(const std::string& textureFile, float scale) override;
    void initSpriteSheet(const std::string& spriteSheetFile) override;
    // Update and draw functions.
    void update(Game* game, float elapsed) override;
    void draw(Window* window) override;
    // Input handling.
    void handleInput(Game& game);

    // Getters for state.
    bool isAttacking() const { return attacking; }
    void setAttacking(bool at) { attacking = at; }
    bool isShouting() const { return shouting; }
    void setShouting(bool sh) { shouting = sh; }

    std::shared_ptr<HealthComponent> getHealthComp() const { return healthComp; }
    int getWood() const { return wood; }
    void addWood(int w);

    // Return velocity component pointer.
    std::shared_ptr<VelocityComponent> getVelocityComp() const { return velocity; }

    // Position the sprite in the tile map.
    void positionSprite(int row, int col, int spriteWH, float tileScale);

    void setObserver(std::shared_ptr<Observer> obs);
    std::shared_ptr<Observer> getObserver() const;

private:
    std::shared_ptr<Fire> createFire() const;
    std::shared_ptr<Observer> observer;

    bool attacking;
    bool shouting;
    std::shared_ptr<HealthComponent> healthComp;
    int wood;
    float shootCooldown;
    std::shared_ptr<InputComponent> input;
    std::shared_ptr<VelocityComponent> velocity;

};
