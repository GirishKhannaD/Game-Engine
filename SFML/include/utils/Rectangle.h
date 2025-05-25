#pragma once
#include "Vector2.h"
#include <SFML/Graphics.hpp>

class Rectangle
{
public:
	Rectangle() : topLeft(Vector2f(0.f,0.f)), bottomRight(Vector2f(0.f, 0.f)) {}
	Rectangle(Vector2f tL, Vector2f bR) : topLeft(tL), bottomRight(bR) {}
	~Rectangle() {}

	void setTopLeft(const Vector2f& tL) { topLeft = tL; }
	void setBottomRight(const Vector2f& bR) { bottomRight = bR; }

	bool intersects(const Rectangle& rect) const;
	bool inside(float x, float y) const;
	bool inside(const Vector2f& point)  const { return inside(point.x, point.y); }

	const Vector2f& getTopLeft() const { return topLeft; }
	const Vector2f& getBottomRight() const { return bottomRight; }

	sf::RectangleShape& getDrawableRect()
	{
		drawableRect.setSize({ bottomRight.x - topLeft.x, bottomRight.y - topLeft.y });
		drawableRect.setPosition(topLeft.x, topLeft.y);
		drawableRect.setFillColor(sf::Color::Transparent);
		drawableRect.setOutlineThickness(4);
		drawableRect.setOutlineColor(sf::Color::Green);
		return drawableRect;
	}

private:
	Vector2f topLeft;
	Vector2f bottomRight;
	sf::RectangleShape drawableRect;
};

