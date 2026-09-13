#pragma once

#include <SFML/Graphics.hpp>
#include "Soldier.hpp"
#include "HealthBar.hpp"
#include "IDamageable.hpp"

class Farm : public IDamageable{
    static constexpr float SIZE = 50.f;
    static constexpr  float MAX_HEALTH = 100.0f;
private:
    Team m_team;
    int m_level;
    float m_health;
    int m_money;
    sf::RectangleShape m_shape;
    HealthBar m_healthBar;
public:
    Farm(bool home, const sf::Vector2u& winSize);
    void draw(sf::RenderWindow& window) const;
    Soldier spawnSoldier(Soldier::Type type) const;

    Team getTeam() const override;
    sf::FloatRect getBounds() const override { return m_shape.getGlobalBounds(); }
    void takeDamage(float amount) override;
    bool isAlive() const override { return m_health > 0.0f; }

    void update(float dt);
    void setHealth(float health) { m_health = health; }
};