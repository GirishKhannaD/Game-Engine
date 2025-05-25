#include "../../include/entities/Entity.h"
#include "../../include/graphics/Window.h"
#include "../../include/utils/Rectangle.h"
#include "../../include/components/PositionComponent.h"
#include <SFML/System/Vector2.hpp>
#include "../../include/utils/Vector2.h"  
#include <iostream>
#include "../../include/utils/Bitmask.h"
#include "../../include/Components/TTLComponent.h"


// Helper function to convert sf::Vector2f to your custom Vector2f type.
inline Vector2f toCustom(const sf::Vector2f& sfv) {
    return Vector2f(sfv.x, sfv.y);
}

Entity::Entity()
    : type(EntityType::UNDEFINED), id(0), isSpriteSheet(false), deleted(false)
{
    // Initialize the position component.
    positionComp = std::make_shared<PositionComponent>();
}

Entity::Entity(EntityType et)
    : type(et), id(0), isSpriteSheet(false), deleted(false)
{
    positionComp = std::make_shared<PositionComponent>();
}

Entity::~Entity() {}

void Entity::init(const std::string& textureFile, float scale) {
    texture.loadFromFile(textureFile);
    sprite.setTexture(texture);
    sprite.setScale(scale, scale);
    // Calculate bounding box size based on texture size and sprite scale.
    bboxSize.x = texture.getSize().x * sprite.getScale().x;
    bboxSize.y = texture.getSize().y * sprite.getScale().y;
}

void Entity::initSpriteSheet(const std::string& spriteSheetFile) {
    spriteSheet.loadSheet(spriteSheetFile);
    isSpriteSheet = true;
    spriteSheet.setAnimation("Idle", true, true);
    bboxSize.x = spriteSheet.getSpriteSize().x * spriteSheet.getSpriteScale().x;
    bboxSize.y = spriteSheet.getSpriteSize().y * spriteSheet.getSpriteScale().y;
}

void Entity::update(Game* /*game*/, float elapsed) {
    // Retrieve the position from the PositionComponent.
    sf::Vector2f pos = positionComp->getPosition();

    if (isSpriteSheet) {
        spriteSheet.getSprite().setPosition(pos.x, pos.y);
        spriteSheet.update(elapsed);
    }
    else {
        sprite.setPosition(pos.x, pos.y);
    }

    // Update the bounding box to reflect the new position.
    boundingBox.setTopLeft(toCustom(pos));
    sf::Vector2f bottomRightPos = { pos.x + bboxSize.x, pos.y + bboxSize.y };
    boundingBox.setBottomRight(toCustom(bottomRightPos));
}

void Entity::draw(Window* window) {
    if (isSpriteSheet)
        window->draw(spriteSheet.getSprite());
    else
        window->draw(sprite);
    window->draw(boundingBox.getDrawableRect());
}

void Entity::setPosition(float x, float y) {
    // Update the position through the PositionComponent.
    positionComp->setPosition(x, y);
    if (isSpriteSheet)
        spriteSheet.getSprite().setPosition(x, y);
    else
        sprite.setPosition(x, y);
}

sf::Vector2f Entity::getPosition() const {
    return positionComp->getPosition();
}

sf::Vector2i Entity::getTextureSize() const {
    if (isSpriteSheet)
        return spriteSheet.getSpriteSize();
    return sf::Vector2i(texture.getSize().x, texture.getSize().y);
}

sf::Vector2f Entity::getSpriteScale() const {
    if (isSpriteSheet)
        return spriteSheet.getSpriteScale();
    return sprite.getScale();
}
