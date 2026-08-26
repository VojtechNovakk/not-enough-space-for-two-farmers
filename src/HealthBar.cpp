#include "HealthBar.hpp"

HealthBar::HealthBar(float width, Anchor anchor) : m_width(width), m_shape(sf::Vector2f(width, BAR_HEIGHT)), m_anchor(anchor){
    m_shape.setFillColor(sf::Color::Red);
}

void HealthBar::updateHealthBar(float healthPercentage) {
    m_shape.setSize(sf::Vector2f( m_width* healthPercentage, BAR_HEIGHT));
}

void HealthBar::draw(sf::RenderWindow& window) const {
    window.draw(m_shape);
}

void HealthBar::update(const sf::Vector2f &position, float percentageHealth) {
    float cur_width = percentageHealth * m_width;
    if (m_anchor == Right)
        m_shape.setPosition(sf::Vector2f(position.x + m_width - cur_width, position.y - BAR_OFFSET));
    else
        m_shape.setPosition(sf::Vector2f(position.x, position.y - BAR_OFFSET));
    m_shape.setSize(sf::Vector2f(cur_width, BAR_HEIGHT));
}
