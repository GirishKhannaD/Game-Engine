#pragma once

#include "Command.h"
#include <memory>
#include <vector>

class Game;

class InputHandler
{
public:
    InputHandler();
    std::shared_ptr<Command> handleInput();

private:
    std::shared_ptr<Command> pauseCommand;
};

enum class InputMode { WASD, ARROWS };

// Player-specific input handler (movement, attack, etc.)
class PlayerInputHandler
{
public:
    PlayerInputHandler();
    std::vector<std::shared_ptr<Command>>& handleInput();
    // Toggle between input modes
    void toggleInputMode();
    InputMode getInputMode() const;

private:
    // Movement commands
    std::shared_ptr<Command> moveRightCommand;
    std::shared_ptr<Command> moveLeftCommand;
    std::shared_ptr<Command> moveUpCommand;
    std::shared_ptr<Command> moveDownCommand;

    // Attack / shout commands
    std::shared_ptr<Command> attackCommand;
    std::shared_ptr<Command> shoutCommand;

    // Command queue is cleared each frame
    std::vector<std::shared_ptr<Command>> commandQueue;

    // Track input mode and toggle state
    InputMode inputMode;
    bool togglePressed = false; // prevents mode toggle from firing repeatedly
};
