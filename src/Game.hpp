#pragma once

#include <SFML/Graphics.hpp>
#include "Farm.hpp"
#include "Soldier.hpp"
#include <string>
#include <vector>
#include <memory>

class Game {
private:
    sf::RenderWindow m_window;
    sf::Clock m_clock;
    std::shared_ptr<Farm> m_homeFarm;
    std::shared_ptr<Farm> m_awayFarm;
    std::vector<std::shared_ptr<Soldier>> m_soldiers;

    void processEvent();
    void handleCollisions() const ;
public:
    Game(const int width, const int height, const std::string& title) : m_window(sf::VideoMode(width, height), title), m_homeFarm(std::make_shared<Farm>(true, sf::Vector2u(width, height))),
    m_awayFarm(std::make_shared<Farm>(false, sf::Vector2u(width, height))) {};
    void run();
};