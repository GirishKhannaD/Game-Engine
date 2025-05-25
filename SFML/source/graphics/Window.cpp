#include "../../include/graphics/Window.h"
#include "../../include/core/Game.h"
#include <iostream>
#include <sstream>
#include <stdexcept>

Window::Window()
    : windowTitle("")
    , windowSize({ 0, 0 })
    , isFullscreen(false)
    , isDone(false)
{
}

Window::~Window() { destroy(); }

void Window::loadFont(const std::string& fontFile)
{
    if (!guiFont.loadFromFile(fontFile)) {
        throw std::runtime_error("Font file not found for Window: " + fontFile);
    }

    // Set up FPS text.
    fpsText.setCharacterSize(fontSize);
    fpsText.setFillColor(sf::Color::Red);
    fpsText.setFont(guiFont);

    // Set up paused text.
    pausedText.setCharacterSize(fontSize + 10);
    pausedText.setFillColor(sf::Color::Blue);
    pausedText.setFont(guiFont);
    pausedText.setString("PAUSED!");

    // Set up health display text.
    healthText.setCharacterSize(fontSize);
    healthText.setFillColor(sf::Color::Green);
    healthText.setFont(guiFont);
    healthText.setPosition(10.f, 60.f);
    healthText.setString("Health: 100/100");
}

void Window::setup(const std::string& title, const sf::Vector2u& size)
{
    windowTitle = title;
    windowSize = size;
    create();
}

void Window::create()
{
    auto style = (isFullscreen ? sf::Style::Fullscreen : sf::Style::Default);
    window.create({ windowSize.x, windowSize.y, 32 }, windowTitle, style);
    pausedText.setPosition(windowSize.x * 0.5f, 0.0f);
}

void Window::destroy()
{
    window.close();
}

void Window::update()
{
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            isDone = true;
        else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F5)
            toggleFullscreen();
    }
}

void Window::toggleFullscreen()
{
    isFullscreen = !isFullscreen;
    redraw();
}

void Window::redraw()
{
    destroy();
    create();
}

void Window::beginDraw() { window.clear(sf::Color::Black); }
void Window::endDraw() { window.display(); }

bool Window::isWindowDone() const { return isDone; }
bool Window::isWindowFullscreen() const { return isFullscreen; }
const sf::Vector2u& Window::getWindowSize() const { return windowSize; }
const sf::Font& Window::getGUIFont() const { return guiFont; }
sf::Text& Window::getFPSText() { return fpsText; }

void Window::drawGUI(const Game& game)
{
    window.draw(fpsText);
    if (game.getPlayer()) {
        auto playerHealth = game.getPlayer()->getHealthComp()->getHealth();
        auto maxHealth = game.getPlayer()->getHealthComp()->getMaxHealth();
        std::ostringstream ss;
        ss << "Health: " << playerHealth << "/" << maxHealth;
        healthText.setString(ss.str());
        window.draw(healthText);
    }
    if (game.isPaused()) {
        window.draw(pausedText);
    }
}

void Window::draw(sf::Drawable& drawable) {
    window.draw(drawable);
}
