#include "Soldier.hpp"

Soldier::Soldier(Type type, Team team, int level, float width, float height, float x, float y) : m_type(type), m_team(team), m_state(Walking),
    m_health(MAX_HEALTH), m_level(level), m_dir(team == Team::Home ? 1 : -1), m_shape(sf::Vector2f(width, height)), m_healthBar(width, team == Team::Home ? HealthBar::Anchor::Left : HealthBar::Anchor::Right) {
    switch (m_type) {
        case Cow:
            m_shape.setFillColor(sf::Color::White);
            m_velocity = 60.0f;
            m_power = 18.0f;
            break;
        case Goat:
            m_shape.setFillColor(sf::Color::Blue);
            m_velocity = 75.0f;
            m_power = 13.0f;
            break;
        case Chicken:
            m_shape.setFillColor(sf::Color::Red);
            m_velocity = 100.0f;
            m_power = 10.0f;
            break;
    }
    m_shape.setPosition(x, y);
}
void Soldier::draw(sf::RenderWindow& window) const {
    window.draw(m_shape);
    m_healthBar.draw(window);
}
void Soldier::update(float sec) {
    if (m_state == State::Walking)
        m_shape.move(sec * m_velocity * static_cast<float>(m_dir), 0.0f);
    m_healthBar.update(m_shape.getPosition(), m_health/MAX_HEALTH);
}
void Soldier::takeDamage(const Soldier& other, float dt) {
    m_health -= other.m_power * dt;
}