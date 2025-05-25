#include "../../include/components/SpriteSheetGraphicsComponent.h"
#include "../../include/entities/Entity.h"

SpriteSheetGraphicsComponent::SpriteSheetGraphicsComponent() {}

SpriteSheetGraphicsComponent::~SpriteSheetGraphicsComponent() {}

void SpriteSheetGraphicsComponent::update(Entity* entity, float elapsed) {
    spriteSheet.update(elapsed);
}

void SpriteSheetGraphicsComponent::draw(Window* window) {
    window->draw(spriteSheet.getSprite());
}
