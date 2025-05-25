#include "../../include/core/InputHandler.h"
#include "../../include/core/Command.h"
#include <SFML/Window/Keyboard.hpp>
#include <vector> 

InputHandler::InputHandler()
{
    pauseCommand = std::make_shared<PauseCommand>();  // Initialize PauseCommand
}

std::shared_ptr<Command> InputHandler::handleInput()
{

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))  // Check for Escape key
    {
        return pauseCommand;  // Return pause command when Escape is pressed
    }
    return nullptr;
}

PlayerInputHandler::PlayerInputHandler()
{
    moveRightCommand = std::make_shared<MoveRightCommand>();
    moveLeftCommand = std::make_shared<MoveLeftCommand>();
    moveUpCommand = std::make_shared<MoveUpCommand>();
    moveDownCommand = std::make_shared<MoveDownCommand>();
    attackCommand = std::make_shared<AttackCommand>();
    shoutCommand = std::make_shared<ShoutCommand>();

    inputMode = InputMode::WASD; // Default to WASD
}

std::vector<std::shared_ptr<Command>>& PlayerInputHandler::handleInput()
{
    commandQueue.clear();

    //Toggle input mode using Enter key (with debounce)
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
        if (!togglePressed) {
            toggleInputMode();
            togglePressed = true;
        }
    }
    else {
        togglePressed = false;
    }

    if (inputMode == InputMode::WASD) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) commandQueue.push_back(moveUpCommand);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) commandQueue.push_back(moveLeftCommand);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) commandQueue.push_back(moveDownCommand);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) commandQueue.push_back(moveRightCommand);
    }
    else if (inputMode == InputMode::ARROWS) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) commandQueue.push_back(moveUpCommand);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) commandQueue.push_back(moveLeftCommand);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) commandQueue.push_back(moveDownCommand);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) commandQueue.push_back(moveRightCommand);
    }

    // Commands common to both modes
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) commandQueue.push_back(attackCommand); //attack command
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) commandQueue.push_back(shoutCommand); //shout command


    return commandQueue;
}

// Toggle between WASD and Arrow input modes
void PlayerInputHandler::toggleInputMode() {
    if (inputMode == InputMode::WASD) {
        inputMode = InputMode::ARROWS;
        std::cout << "[InputHandler] Switched to ARROWS mode\n";
    }
    else {
        inputMode = InputMode::WASD;
        std::cout << "[InputHandler] Switched to WASD mode\n";
    }
}

InputMode PlayerInputHandler::getInputMode() const {
    return inputMode;
}