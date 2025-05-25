#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include "include/core/Game.h"

void adaptiveLoop(Game& game, float& lastTime, float updateTarget = 0)
{
    float current = game.getElapsed().asSeconds();
    float elapsedSeconds = current - lastTime;

    //Three function calls for the game loop: handleInput, update and render.
    game.handleInput();
    game.update(elapsedSeconds);
    game.render(elapsedSeconds);

    //Sleep to reach constant framerate.
    if (elapsedSeconds < updateTarget)
    {
        sf::sleep(sf::seconds(updateTarget - elapsedSeconds));
    }

    //Calculate FPS.
    float fps = 1.0f / elapsedSeconds;
    game.setFPS(static_cast<int>(fps));

    std::cout << "FPS: " << fps << "; elapsed: " << std::fixed << elapsedSeconds << std::endl;

    lastTime = current;
}

int main(int argc, char** argv)
{
    // Try to load the level:
    std::ifstream levelRead{ "levels/lvl0.txt" };
    if (!levelRead)
    {
        throw std::exception("File not found\n");
    }

    // Convert file to vector of strings:
    std::vector<std::string> lines;
    while (levelRead)
    {
        std::string strInput;
        std::getline(levelRead, strInput);
        lines.emplace_back(strInput);
    }

    // Create and initialize the game.
    Game game;
    game.init(lines);

    // GAME LOOP (targeting 60FPS)
    float updateTarget = 0.016f; // 60 FPS = ~0.016 sec per frame
    float lastTime = game.getElapsed().asSeconds();

    while (!game.getWindow()->isWindowDone())
    {
        adaptiveLoop(game, lastTime, updateTarget);
    }

    // Pause before exiting so you can see console output.
    std::cout << "Press Enter to exit...";
    std::cin.get();

    return 0;
}
