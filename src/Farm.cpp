#include "Farm.hpp"

#include "IDamageable.hpp"
#include "IDamageable.hpp"
#include "IDamageable.hpp"

Farm::Farm(bool home, const sf::Vector2u& winSize) : m_team(home ? Team::Home : Team::Away), m_level(1), m_health(MAX_HEALTH), m_money(0), m_shape(sf::Vector2f(SIZE, SIZE)), m_healthBar(SIZE, m_team == Team::Home ? HealthBar::Anchor::Left : HealthBar::Anchor::Right) {
    if (home)
        m_shape.setPosition(0.0f, static_cast<float>(winSize.y) - SIZE);
    else
        m_shape.setPosition(static_cast<float>(winSize.x) - SIZE, static_cast<float>(winSize.y) - SIZE);
    m_shape.setFillColor(sf::Color::Red);
}

Soldier Farm::spawnSoldier(Soldier::Type type) const {
    sf::Vector2f farmPos = m_shape.getPosition();
    return Soldier(type, m_team, m_level, 15.0f, 40.0f, m_team == Team::Home ? farmPos.x+30.0f : farmPos.x+SIZE-30.0f, farmPos.y+SIZE-40.0f);
}

void Farm::draw(sf::RenderWindow& window) const {
    window.draw(m_shape);
    m_healthBar.draw(window);
}

Farm::Team Farm::getTeam() const { return m_team; }

void Farm::takeDamage(float amount) {
    m_health -= amount;
}

void Farm::update(float dt) {
    m_healthBar.update(m_shape.getPosition(), m_health / MAX_HEALTH);
}
