#pragma once

#include <SFML/Graphics.hpp>
#include "Farm.hpp"
#include "Soldier.hpp"
#include <string>
#include <vector>

class Game {
private:
    sf::RenderWindow m_window;
    sf::Clock m_clock;
    Farm m_homeFarm;
    Farm m_awayFarm;
    std::vector<Soldier> m_soldiers;

    void processEvent();
    void handleCollisions(float dt);
public:
    Game(const int width, const int height, const std::string& title) : m_window(sf::VideoMode(width, height), title), m_homeFarm(true, sf::Vector2u(width, height)), m_awayFarm(false, sf::Vector2u(width, height)) {};
    void run();
};