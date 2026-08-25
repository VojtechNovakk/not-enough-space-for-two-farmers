#include "Soldier.hpp"

void Soldier::draw(sf::RenderWindow& window) const { window.draw(m_shape); }
void Soldier::update() {
    const sf::Vector2f pos = m_shape.getPosition();
    m_shape.setPosition(pos.x + m_velocity, pos.y);
}