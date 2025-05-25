#include "../../include/core/Game.h"
#include "../../include/entities/Fire.h"
#include "../../include/entities/StaticEntities.h"
#include <iostream>
#include "../../include/core/Command.h"
#include "../../include/core/InputHandler.h"
#include <algorithm>
#include <sstream>
#include "../../include/systems/Systems.h"
#include "../../include/utils/Observer.h"
#include "../../include/core/AudioManager.h"
#include "../../include/core/ServiceLocator.h"

void Game::registerCollisionCallback(EntityType type, std::function<void(Entity*)> callback) {
    collisionCallbacks[type] = callback;
}

std::shared_ptr<AudioManager> ServiceLocator::audioService = nullptr;

Game::Game(ECSType type)
    : paused(false), entityCounter(1), ecsType(type)
{
    inputHandler = std::make_unique<InputHandler>();

    //added the remaining systems
    systems.push_back(std::make_shared<InputSystem>());
    systems.push_back(std::make_shared<MovementSystem>());
    systems.push_back(std::make_shared<ColliderSystem>());
    systems.push_back(std::make_shared<GameplaySystem>());
    systems.push_back(std::make_shared<PrintDebugSystem>());

    graphicsSystems.push_back(std::make_shared<GraphicsSystem>());

    // Initialize archetypes if ECS type is ARCHETYPES
    if (ecsType == ECSType::ARCHETYPES) {
        // Archetype initialization
        Archetype movableEntities;
        movableEntities.componentMask.turnOnBit(static_cast<unsigned int>(ComponentID::VELOCITY));
        movableEntities.componentMask.turnOnBit(static_cast<unsigned int>(ComponentID::POSITION));

        Archetype drawableEntities;
        drawableEntities.componentMask.turnOnBit(static_cast<unsigned int>(ComponentID::GRAPHICS));

        archetypes.push_back(movableEntities);
        archetypes.push_back(drawableEntities);
    }


    //Initialized TTLSystem and add it to systems vector
    auto ttlSystem = std::make_shared<TTLSystem>();
    systems.push_back(ttlSystem);

}

// Big array function
void Game::bigArray(float elapsed) {
    for (const auto& sys : systems) {
        for (auto& ent : entities) {
            if (sys->validate(ent.get())) {
                sys->update(this, ent.get(), elapsed);
            }
        }
    }
}



Game::~Game() {}

void Game::init(std::vector<std::string> lines)
{
    size_t h = lines.size();
    if (h == 0) throw std::exception("No data in level file");
    size_t w = static_cast<size_t>(-1);

    window.loadFont("font/AmaticSC-Regular.ttf");
    window.setTitle("Mini-Game");

    // INIT AUDIO MANAGER and REGISTER SERVICE LOCATOR
    auto audio = std::make_shared<AudioManager>();
    audio->loadSound("pickup", "audio/potion_collect.wav");
    audio->loadSound("fire", "audio/fire.wav");
    audio->loadSound("axe", "audio/sword-slash.wav");
    ServiceLocator::provide(audio);

    auto it = lines.cbegin();
    int row = 0;
    while (it != lines.cend())
    {
        int col = 0;
        if (w == static_cast<size_t>(-1))
        {
            w = it->size();
            buildBoard(w, h);
            initWindow(w, h);
        }
        std::string::const_iterator is = it->cbegin();
        while (is != it->cend())
        {
            switch (*is)
            {
                case '.':
                    board->addTile(col, row, tileScale, TileType::CORRIDOR, "img/floor.png");
                    break;
                case 'w':
                    board->addTile(col, row, tileScale, TileType::WALL, "img/wall.png");
                    break;
                case 'x':
                {
                    auto ent = buildEntityAt<Log>("img/log.png", col, row);
                    addEntity(ent);
                    board->addTile(col, row, tileScale, TileType::CORRIDOR, "img/floor.png");
                    break;
                }
                case 'p':
                {
                    auto ent = buildEntityAt<Potion>("img/potion.png", col, row);
                    addEntity(ent);
                    board->addTile(col, row, tileScale, TileType::CORRIDOR, "img/floor.png");
                    break;
                }
                case '*':
                {
                    player = std::make_shared<Player>();
                    player->initSpriteSheet("img/DwarfSpriteSheet_data.txt");
                    player->positionSprite(row, col, spriteWH, tileScale);
                    addEntity(player);
                    board->addTile(col, row, tileScale, TileType::CORRIDOR, "img/floor.png");

                    // Observer Pattern: Create and assign
                    achievementObserver = std::make_shared<AchievementObserver>();
                    player->setObserver(achievementObserver);
					// Register collision callbacks
                    registerCollisionCallback(EntityType::POTION, std::bind(&Player::handlePotionCollision, player.get(), std::placeholders::_1));
                    registerCollisionCallback(EntityType::LOG, std::bind(&Player::handleLogCollision, player.get(), std::placeholders::_1));
                    break;
                }
            }
            col++;
            is++;
        }
        row++;
        it++;
    }
}

void Game::addEntity(std::shared_ptr<Entity> newEntity)
{
    entityCounter++;
    newEntity->setID(entityCounter);
    entities.push_back(newEntity);

    // Add entity to corresponding archetypes if using Archetypes ECS
    if (ecsType == ECSType::ARCHETYPES) {
        for (auto& archetype : archetypes) {
            if (newEntity->hasComponent(archetype.componentMask)) {
                archetype.entities.push_back(newEntity);
            }
        }
    }
    else if (ecsType == ECSType::PACKED_ARRAY) {
        packedEntities.insert(newEntity->getID(), newEntity);
    }
}

void Game::handleInput()
{
    auto cmd = inputHandler->handleInput();
    if (cmd) { cmd->execute(*this); }
    if (player) { player->handleInput(*this); }
}

void Game::update(float elapsed)
{

    if (!paused) {
        bigArray(elapsed);

        for (auto& ent : entities) {
            ent->update(this, elapsed);
        }
    }

    if (ecsType == ECSType::ARCHETYPES)
        updateArchetypes(elapsed);  // Use Archetypes ECS
    else if (ecsType == ECSType::PACKED_ARRAY)
        updatePackedArray(elapsed); // Packed ECS update
    else
        bigArray(elapsed);          // Use Big Array ECS (existing)


    // Collision handling for static entities.
    Rectangle& playerBB = player->getBoundingBox();
    for (auto& ent : entities) {
        if (ent == player) continue;
        Rectangle& eBB = ent->getBoundingBox();
        if (playerBB.intersects(eBB)) {
            auto it = collisionCallbacks.find(ent->getEntityType());
            if (it != collisionCallbacks.end()) {                    
                it->second(ent.get());                               
            }                                                       
            
        }
    }

    // Remove deleted entities.
    entities.erase(
        std::remove_if(entities.begin(), entities.end(),
            [](std::shared_ptr<Entity>& e) { return e->isDeleted(); }),
        entities.end()
    );

    window.update();
}

// New updateArchetypes method (implementing Archetypes ECS logic)
void Game::updateArchetypes(float elapsed) {
    // Iterate over each archetype
    for (auto& archetype : archetypes) {
        for (auto& entity : archetype.entities) {
            // Iterate through systems and update relevant entities
            for (auto& sys : systems) {
                if (sys->validate(entity.get()))
                    sys->update(this, entity.get(), elapsed);
            }
        }
    }
}

// Packed ECS loop
void Game::updatePackedArray(float elapsed) {
    for (auto& sys : systems) {
        for (auto& ent : packedEntities.getDense()) {
            if (sys->validate(ent.get())) {
                sys->update(this, ent.get(), elapsed);
            }
        }
    }
}

void Game::render(float elapsed)
{
    window.beginDraw();
    if (board) { board->draw(&window); }
    for (auto& ent : entities) {
        ent->draw(&window);
    }
    window.drawGUI(*this);
    window.endDraw();
}

sf::Time Game::getElapsed() const
{
    return gameClock.getElapsedTime();
}

void Game::setFPS(int fps)
{
    std::cout << "FPS: " << fps << std::endl;
}

void Game::buildBoard(size_t width, size_t height)
{
    board = std::make_unique<Board>(width, height);
}

void Game::initWindow(size_t width, size_t height)
{
    int wdt = static_cast<int>(width * spriteWH * tileScale);
    int hgt = static_cast<int>(height * spriteWH * tileScale);
    window.setSize(sf::Vector2u(wdt, hgt));
    window.redraw();
}

EntityID Game::getIDCounter()
{
    return entityCounter;
}

std::shared_ptr<Entity> Game::getEntity(unsigned int idx)
{
    if (idx < 1 || idx > entities.size())
        return nullptr;
    return entities[idx - 1];
}
