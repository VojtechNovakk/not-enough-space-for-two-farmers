#pragma once

#include <SFML/Graphics.hpp>
#include "Soldier.hpp"
#include <vector>

class Farm{
    static constexpr float SIZE = 50.f;
private:
    bool m_home;
    int m_level;
    int m_health;
    int m_money;
    std::vector<Soldier> m_soldiers;
    sf::RectangleShape m_shape;
public:
    Farm(bool home, const sf::Vector2u& winSize);
    void draw(sf::RenderWindow& window) const;
    void update(float sec);
    void addSoldier(Soldier::Type type);
};