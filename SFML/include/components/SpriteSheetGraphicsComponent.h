#pragma once
#include "GraphicsComponent.h"
#include "../../include/graphics/SpriteSheet.h"

class SpriteSheetGraphicsComponent : public GraphicsComponent {
public:
    SpriteSheetGraphicsComponent();
    ~SpriteSheetGraphicsComponent() override;
    void update(Entity* entity, float elapsed) override;
    void draw(Window* window) override;
    SpriteSheet* getSpriteSheet() override { return &spriteSheet; }
private:
    SpriteSheet spriteSheet;
};
