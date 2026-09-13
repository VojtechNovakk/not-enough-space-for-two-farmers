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
    std::shared_ptr<Farm> m_homeFarm;
    std::shared_ptr<Farm> m_awayFarm;
    std::vector<std::shared_ptr<Soldier>> m_soldiers;
    State m_state = State::Menu;
    Menu m_menu;
    EndScreen m_endScreen;

    void startGame();
    void endGame(Winner winner);
    void processEvent();
    void handleCollisions() const ;
public:
    Game(const int width, const int height, const std::string& title) : m_window(sf::VideoMode(width, height), title), m_homeFarm(std::make_shared<Farm>(true, sf::Vector2u(width, height))),
    m_awayFarm(std::make_shared<Farm>(false, sf::Vector2u(width, height))), m_menu(m_window.getSize()), m_endScreen(m_window.getSize()) {};
    void run();
};