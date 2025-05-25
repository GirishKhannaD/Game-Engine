#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include "AnimBase.h"

using Animations = std::unordered_map<std::string, AnimBase*>;
enum class Direction { Right = 0, Left };

class SpriteSheet {
public:
    SpriteSheet();
    ~SpriteSheet();

    void releaseSheet();
    void setSpriteSize(const sf::Vector2i& size);
    void setSpriteScale(const sf::Vector2f& scale);
    void setSpritePosition(const sf::Vector2f& pos);
    void setSpriteDirection(const Direction& dir);

    const sf::Vector2i& getSpriteSize() const { return spriteSize; }
    const sf::Vector2f& getSpriteScale() const { return spriteScale; }
    const Direction& getSpriteDirection() const { return direction; }
    const sf::Vector2f& getSpritePosition() const { return sprite.getPosition(); }
    const std::string& getAnimType() const { return animType; }
    size_t getNumAnimations() const { return animations.size(); }
    sf::Sprite& getSprite() { return sprite; }

    void cropSprite(const sf::IntRect& rect);
    bool loadSheet(const std::string& file);

    AnimBase* getCurrentAnim() const;

    bool setAnimation(const std::string& name, bool play = false, bool loop = false);

    void update(float elapsedTime);
    void draw(sf::RenderWindow* window);

private:
    sf::Texture texture;
    sf::Sprite sprite;
    sf::Vector2i spriteSize;
    sf::Vector2f spriteScale;
    Direction direction;
    std::string animType;
    Animations animations;
    AnimBase* curAnimation;
};
