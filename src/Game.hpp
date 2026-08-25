#pragma once

#include <SFML/Graphics.hpp>
#include "Farm.hpp"
#include "Soldier.hpp"
#include <string>

class Game {
private:
    sf::RenderWindow m_window;
    sf::Clock m_clock;
    Farm m_homeFarm;
    Farm m_awayFarm;
    void processEvent();
public:
    Game(const int width, const int height, const std::string& title) : m_window(sf::VideoMode(width, height), title), m_homeFarm(true, sf::Vector2u(width, height)), m_awayFarm(false, sf::Vector2u(width, height)) {};
    void run();
};