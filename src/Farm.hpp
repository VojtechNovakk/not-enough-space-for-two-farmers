#pragma once

#include <SFML/Graphics.hpp>
#include "Soldier.hpp"
#include "HealthBar.hpp"

class Farm{
    static constexpr float SIZE = 50.f;
    static constexpr  float MAX_HEALTH = 100.0f;
private:
    bool m_home;
    int m_level;
    float m_health;
    int m_money;
    sf::RectangleShape m_shape;
    HealthBar m_healthBar;
public:
    Farm(bool home, const sf::Vector2u& winSize);
    void draw(sf::RenderWindow& window) const;
    Soldier spawnSoldier(Soldier::Type type) const;
    sf::FloatRect getBounds() const { return m_shape.getGlobalBounds(); }
    void update(float dt);
};