#pragma once
#include <SFML/Graphics.hpp>
#include <string>
class Game;

class Window {
public:
    Window();
    ~Window();

    void loadFont(const std::string& fontFile);
    void beginDraw();
    void endDraw();

    void update();

    bool isWindowDone() const;
    bool isWindowFullscreen() const;
    const sf::Vector2u& getWindowSize() const;
    const sf::Font& getGUIFont() const;
    sf::Text& getFPSText();

    void toggleFullscreen();
    void draw(sf::Drawable& drawable);
    void redraw();
    void drawGUI(const Game& game);

    void setup(const std::string& title, const sf::Vector2u& size);
    inline void setTitle(const std::string& t) { windowTitle = t; }
    inline void setSize(const sf::Vector2u& size) { windowSize = size; }

private:
    const int fontSize = 50;

    void destroy();
    void create();

    sf::RenderWindow window;
    sf::Vector2u windowSize;
    std::string windowTitle;
    sf::Font guiFont;
    sf::Text fpsText;
    sf::Text pausedText;
    sf::Text healthText;

    bool isDone;
    bool isFullscreen;
};
