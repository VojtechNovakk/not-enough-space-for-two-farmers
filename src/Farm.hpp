#pragma once

#include <SFML/Graphics.hpp>
#include "Soldier.hpp"

class Farm{
    static constexpr float SIZE = 50.f;
private:
    bool m_home;
    int m_level;
    int m_health;
    int m_money;
    sf::RectangleShape m_shape;
public:
    Farm(bool home, const sf::Vector2u& winSize);
    void draw(sf::RenderWindow& window) const;
    Soldier spawnSoldier(Soldier::Type type) const;
    sf::FloatRect getBounds() const { return m_shape.getGlobalBounds(); }
};