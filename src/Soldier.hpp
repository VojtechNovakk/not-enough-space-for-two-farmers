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
    sf::RectangleShape m_shape;
public:
    Soldier(Type type, int level, int width, int height, float x, float y) : m_type(type), m_health(100), m_level(level), m_shape(sf::Vector2f(width, height)) {
        switch (m_type) {
            case Cow:
                m_shape.setFillColor(sf::Color::White);
                m_velocity = 0.8;
                break;
            case Goat:
                m_shape.setFillColor(sf::Color::Blue);
                m_velocity = 1.0;
                break;
            case Chicken:
                m_shape.setFillColor(sf::Color::Red);
                m_velocity = 1.2;
                break;
            default:
                m_shape.setFillColor(sf::Color::Yellow);
                m_velocity = 0.1;
        }
        m_shape.setPosition(x, y);
    }
    void draw(sf::RenderWindow& window) const;
    void update();
};