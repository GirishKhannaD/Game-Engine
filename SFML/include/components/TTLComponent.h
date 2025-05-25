#pragma once
#include "Components.h"

class TTLComponent: public Component{
public:
    ComponentID getID() const override {
        return ComponentID::TTL;
    }

    // Constructor: initialize ttl with the provided initial value.
    TTLComponent(int initialTTL) : ttl(initialTTL) {}

    // update(): subtract 1 from ttl if it's greater than 0.
    void update() {
        if (ttl > 0) {
            --ttl;
        }
    }

    // getTTL(): returns the current ttl value.
    int getTTL() const {
        return ttl;
    }
    void decrementTTL() { if (ttl > 0) --ttl; }


private:
    int ttl; // Time-to-live counter.
};
