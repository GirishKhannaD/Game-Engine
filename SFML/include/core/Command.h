#pragma once
#include <memory>
#include "Game.h"
#include "../../include/entities/Player.h"

class Game;

// Base Command class
class Command
{
    public:
        virtual ~Command() = default;
        virtual void execute(Game& game) = 0; // Pure virtual function
};

// PauseCommand class
class PauseCommand : public Command
{
    public:
        void execute(Game& game) override;
};

// Movement Commands
class MoveRightCommand : public Command
{
    public:
        void execute(Game& game) override;
};

class MoveLeftCommand : public Command
{
    public:
        void execute(Game& game) override;
};

class MoveUpCommand : public Command
{
    public:
        void execute(Game& game) override;
};

class MoveDownCommand : public Command
{
    public:
        void execute(Game& game) override;
};

class AttackCommand : public Command
{
    public:
        void execute(Game& game) override;
};

class ShoutCommand : public Command
{
    public:
        void execute(Game& game) override;
        
};