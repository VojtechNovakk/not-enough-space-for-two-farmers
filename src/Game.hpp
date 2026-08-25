#pragma once

#include <SFML/Graphics.hpp>
#include <Soldier.hpp>
#include <string>
#include <vector>

class Game {
private:
    sf::RenderWindow m_window;
    int m_width;
    int m_height;
    std::vector<Soldier> m_soldiers;
    void processEvent();
public:
    Game(const int width, const int height, const std::string& title) : m_window(sf::VideoMode(width, height), title), m_width(width), m_height(height) {};
    void run();
};