#pragma once
#include <algorithm>
#include <stdexcept>
#include <string>
#include "Components.h"

class HealthComponent:public Component{

public:
    ComponentID getID() const override {
        return ComponentID::HEALTH;
    }

    // Constructor: initialize current and maximum health using an initializer list.
    HealthComponent(int startingHealth, int maximumHealth)
        : currentHealth(startingHealth), maxHealth(maximumHealth)
    {
        if (startingHealth < 0 || startingHealth > maximumHealth) {
            throw std::invalid_argument("Invalid starting health value");
        }
    }

    // Returns the current health value.
    int getHealth() const { return currentHealth; }

    // Returns the maximum health value.
    int getMaxHealth() const { return maxHealth; }

    // Adjusts the current health by delta, clamping the value between 0 and maxHealth.
    void changeHealth(int delta) {
        currentHealth += delta;
        currentHealth = std::max(0, std::min(currentHealth, maxHealth));
    }

protected:
    int currentHealth;
    int maxHealth;
};
