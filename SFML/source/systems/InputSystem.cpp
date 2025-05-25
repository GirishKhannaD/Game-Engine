#include "../../include/systems/Systems.h"
#include "../../include/components/InputComponent.h"
#include "../../include/entities/Entity.h"
#include "../../include/core/Game.h"
#include <memory>

InputSystem::InputSystem() {
    // Set the component mask to require an InputComponent.
    componentMask.turnOnBit(static_cast<unsigned int>(ComponentID::INPUT));
}

void InputSystem::update(Game* game, Entity* entity, float elapsed) {
    // Retrieve the InputComponent from the entity.
    // Using the entity's getComponent() function which returns a shared_ptr<Component>.
    std::shared_ptr<Component> comp = entity->getComponent(ComponentID::INPUT);

    // Attempt to cast it to an InputComponent.
    std::shared_ptr<InputComponent> inputComp = std::dynamic_pointer_cast<InputComponent>(comp);

    // If the entity has an InputComponent, call its update() function.
    if (inputComp) {
        inputComp->update(*game);
    }
}
