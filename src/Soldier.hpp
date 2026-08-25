#pragma once

#include <SFML/Graphics.hpp>

class Soldier {
public:
    enum Type {
        Cow,
        Goat,
        Chicken
    };
private:
    Type m_type;
    int m_health;
    int m_level;
    float m_velocity;
    int m_dir;
    sf::RectangleShape m_shape;
public:
    Soldier(Type type, int level, float width, float height, int dir, float x, float y);
    void draw(sf::RenderWindow& window) const;
    void update(float sec);
};