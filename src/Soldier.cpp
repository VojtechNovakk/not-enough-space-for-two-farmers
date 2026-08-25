#include "Soldier.hpp"

Soldier::Soldier(Type type, int level, float width, float height, int dir, float x, float y) : m_type(type), m_health(100), m_level(level), m_dir(dir), m_shape(sf::Vector2f(width, height)) {
    switch (m_type) {
        case Cow:
            m_shape.setFillColor(sf::Color::White);
            m_velocity = 60.0f;
            break;
        case Goat:
            m_shape.setFillColor(sf::Color::Blue);
            m_velocity = 75.0f;
            break;
        case Chicken:
            m_shape.setFillColor(sf::Color::Red);
            m_velocity = 100.0f;
            break;
    }
    m_shape.setPosition(x, y);
}
void Soldier::draw(sf::RenderWindow& window) const { window.draw(m_shape); }
void Soldier::update(float sec) {
    m_shape.move(sec * m_velocity * static_cast<float>(m_dir), 0.0f);
}