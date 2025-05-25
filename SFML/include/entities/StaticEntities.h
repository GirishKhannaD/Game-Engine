#pragma once
#include "Entity.h"
#include "../utils/Vector2.h"
#include <string>


inline Vector2f toCustom(const sf::Vector2f& sfv) {
    return Vector2f(sfv.x, sfv.y);
}

class Potion : public Entity {
public:
    Potion() : Entity(EntityType::POTION) {}
    ~Potion() {}

    void init(const std::string& textureFile, float scale) override {
        Entity::init(textureFile, scale);
        sf::Vector2f pos = getPosition();
        boundingBox.setTopLeft(toCustom(pos));
        sf::Vector2f bottomRightPos = { pos.x + bboxSize.x, pos.y + bboxSize.y };
        boundingBox.setBottomRight(toCustom(bottomRightPos));
    }

    void update(Game*, float = 1.0f) override {}
    int getHealth() const { return potionHealth; }
protected:
    const int potionHealth = 10;
};

class Log : public Entity {
public:
    Log() : Entity(EntityType::LOG) {}
    ~Log() {}

    void init(const std::string& textureFile, float scale) override {
        Entity::init(textureFile, scale);
        sf::Vector2f pos = getPosition();
        boundingBox.setTopLeft(toCustom(pos));
        sf::Vector2f bottomRightPos = { pos.x + bboxSize.x, pos.y + bboxSize.y };
        boundingBox.setBottomRight(toCustom(bottomRightPos));
    }

    void update(Game*, float= 1.0f) override {}
    int getWood() const { return woodAdded; }
protected:
    const int woodAdded = 15;
};
