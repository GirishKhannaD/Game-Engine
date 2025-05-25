#pragma once
#include "../../include/graphics/Window.h"
#include "../../include/core/Board.h"
#include "../../include/entities/Player.h"
#include "Command.h"
#include <memory>
#include <vector>
#include <string>
#include <SFML/System/Time.hpp>
#include "../../include/systems/Systems.h"
#include "../../include/utils/PackedArray.h"
#include "../../include/utils/Observer.h"
#include <unordered_map>
#include <functional> 

class InputHandler;
class Player;
class Entity;
class System;

using EntityID = unsigned int;
enum class ECSType { BIG_ARRAY, ARCHETYPES, PACKED_ARRAY };
class Archetype {
public:
    std::vector<std::shared_ptr<Entity>> entities; // Entities sharing the same component structure
    Bitmask componentMask;                         // Bitmask representing common components
};

class Game {
public:
    const int spriteWH = 50;
    const float tileScale = 2.0f;
    const float itemScale = 1.0f;

    void registerCollisionCallback(EntityType type, std::function<void(Entity*)> callback);

    Game(ECSType type = ECSType::BIG_ARRAY);
    ~Game();

    void init(std::vector<std::string> lines);
    void addEntity(std::shared_ptr<Entity> newEntity);

    void buildBoard(size_t width, size_t height);
    void initWindow(size_t width, size_t height);

    void handleInput();
    void update(float elapsed);
    void render(float elapsed);
    Window* getWindow() { return &window; }

    sf::Time getElapsed() const;
    void setFPS(int FPS);
    void togglePause() { paused = !paused; }
    bool isPaused() const { return paused; }

    std::shared_ptr<Player> getPlayer() const { return player; }

    EntityID getIDCounter();
    std::shared_ptr<Entity> getEntity(unsigned int idx);

    template <typename T>
    std::shared_ptr<T> buildEntityAt(const std::string& filename, int col, int row)
    {
        auto ent = std::make_shared<T>();
        float x = col * spriteWH * tileScale;
        float y = row * spriteWH * tileScale;
        float cntrFactor = (tileScale - itemScale) * spriteWH * 0.5f;
        ent->setPosition(x + cntrFactor, y + cntrFactor);
        ent->init(filename, itemScale);
        return ent;
    }

private:

    //method specific to Archetypes ECS
    void updateArchetypes(float elapsed);
    void bigArray(float elapsed);
    void updatePackedArray(float elapsed);
    Window window;
    bool paused;
    sf::Clock gameClock;
    sf::Time elapsed;

    std::unique_ptr<Board> board;
    std::vector<std::shared_ptr<Entity>> entities;
    std::vector<std::shared_ptr<System>> systems;
    EntityID entityCounter;
    std::shared_ptr<Player> player;
    std::unique_ptr<InputHandler> inputHandler;
    std::vector<std::shared_ptr<System>> graphicsSystems;
    //variables for ECS architecture selection
    ECSType ecsType;
    std::vector<Archetype> archetypes;  // For Archetypes ECS
    PackedArray<Entity> packedEntities; // Packed storage

    // Added Observer Pattern support
    std::shared_ptr<AchievementObserver> achievementObserver;
    std::unordered_map<EntityType, std::function<void(Entity*)>> collisionCallbacks;
};
