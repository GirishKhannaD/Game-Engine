#pragma once
#include <iostream>

class Observer {
public:
    virtual void onPotionCollected() = 0;
    virtual void onShoutPerformed() = 0;
};

class AchievementObserver : public Observer {
    int potionsCollected = 0;
    int shoutsPerformed = 0;

    const int requiredPotions = 6; //dynamically count them
    const int requiredShouts = 5;

public:
    void onPotionCollected() override {
        potionsCollected++;
        if (potionsCollected == requiredPotions) {
            std::cout << "Achievement unlocked: All potions collected!\n";
        }
    }

    void onShoutPerformed() override {
        shoutsPerformed++;
        if (shoutsPerformed == requiredShouts) {
            std::cout << "Achievement unlocked: Shouted 5 times!\n";
        }
    }
};
