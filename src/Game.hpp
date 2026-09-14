#pragma once

#include <SFML/Graphics.hpp>
#include "Farm.hpp"
#include "Soldier.hpp"
#include "Menu.hpp"
#include "EndScreen.hpp"
#include <string>
#include <vector>
#include <memory>

class Game {
public:
    enum class State { Menu, Playing, GameOver};
    enum class Winner { None, Home, Away };
private:
    sf::RenderWindow m_window;
    sf::Clock m_clock;
    sf::Font m_font;

    sf::Texture m_bgTexture;
    sf::Texture m_farmTexture;

    sf::Sprite m_background;
    std::shared_ptr<Farm> m_homeFarm;
    std::shared_ptr<Farm> m_awayFarm;
    std::vector<std::shared_ptr<Soldier>> m_soldiers;
    State m_state = State::Menu;
    Menu m_menu;
    EndScreen m_endScreen;

    static sf::Font loadFont(const std::string& path);
    static sf::Texture loadTexture(const std::string& path);
    void startGame();
    void endGame(Winner winner);
    void processEvent();
    void handleCollisions() const ;
public:
    Game(const int width, const int height, const std::string& title);
    void run();
};