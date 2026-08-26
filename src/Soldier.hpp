#pragma once

#include <SFML/Graphics.hpp>
#include "HealthBar.hpp"

class Soldier {
    static constexpr float MAX_HEALTH = 100.0f;
public:
    enum Type {
        Cow,
        Goat,
        Chicken
    };
    enum Team {
        Home,
        Away
    };
    enum State {
        Walking,
        Fighting
    };
private:
    Type m_type;
    Team m_team;
    State m_state;
    float m_health;
    int m_level;
    float m_velocity;
    int m_dir;
    float m_power;
    sf::RectangleShape m_shape;
    HealthBar m_healthBar;
public:
    Soldier(Type type, Team team, int level, float width, float height, float x, float y);
    void draw(sf::RenderWindow& window) const;
    void update(float sec);
    sf::FloatRect getBounds() const { return m_shape.getGlobalBounds(); }
    Team getTeam() const { return m_team; }
    float getHealth() const { return m_health; }
    void setState(State new_state) { m_state = new_state; }
    void takeDamage(const Soldier& other, float dt);
};