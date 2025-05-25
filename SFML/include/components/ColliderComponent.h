#pragma once
#include "../../include/utils/Rectangle.h"
#include <memory>
#include <SFML/System/Vector2.hpp>
#include "Components.h"

class Window;

class ColliderComponent: public Component{
public:
    ComponentID getID() const override {
        return ComponentID::COLLIDER;
    }

    // Construct with an initial bounding box.
    ColliderComponent(const Rectangle& rect) : boundingBox(rect) {}
    virtual ~ColliderComponent() = default;

    // Update bounding box position and size based on entity position and sprite size.
    virtual void update(const sf::Vector2f& pos, const sf::Vector2f& size) {
        boundingBox.setTopLeft({ pos.x, pos.y });
        boundingBox.setBottomRight({ pos.x + size.x, pos.y + size.y });
    }

    // Draw bounding box (for debugging).
    virtual void draw(Window* window) {
        window->draw(boundingBox.getDrawableRect());
    }

    const Rectangle& getBoundingBox() const { return boundingBox; }

    bool intersects(const ColliderComponent& other) const {
        return boundingBox.intersects(other.getBoundingBox());
    }
private:
    Rectangle boundingBox;
};
