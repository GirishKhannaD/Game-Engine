#pragma once
enum class ComponentID
{
	UNDEFINED = -1, // default value .
	INPUT = 0,
	POSITION,
	VELOCITY,
    COLLIDER,
    GRAPHICS,
    HEALTH,
    LOGIC,
    TTL,
    COUNT
};

class Component
{
public:
    virtual ~Component() = default;
    virtual ComponentID getID() const = 0;
};