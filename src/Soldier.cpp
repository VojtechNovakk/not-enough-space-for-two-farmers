#include "Soldier.hpp"

Soldier::Soldier(Type type, Team team, int level, float width, float height, float x, float y) : m_type(type), m_team(team), m_state(Walking), m_level(level), m_dir(team == Team::Home ? 1 : -1), m_shape(sf::Vector2f(width, height)), m_healthBar(width, team == Team::Home ? HealthBar::Anchor::Left : HealthBar::Anchor::Right) {
    switch (m_type) {
        case Cow:
            m_shape.setFillColor(sf::Color::White);
            m_velocity = 60.0f;
            m_power = 35.0f;
            m_attackRange = 8.0f;
            m_maxHealth = 200.0f;
            break;
        case Goat:
            m_shape.setFillColor(sf::Color::Blue);
            m_velocity = 75.0f;
            m_power = 25.0f;
            m_attackRange = 5.0f;
            m_maxHealth = 100.0f;
            break;
        case Chicken:
            m_shape.setFillColor(sf::Color::Red);
            m_velocity = 100.0f;
            m_power = 17.0f;
            m_attackRange = 60.0f;
            m_maxHealth = 75.0f;
            break;
    }
    m_health = m_maxHealth;
    m_shape.setPosition(x, y);
}
void Soldier::draw(sf::RenderWindow& window) const {
    window.draw(m_shape);
    m_healthBar.draw(window);
}
void Soldier::update(float sec) {
    m_state = hasValidTarget() ? State::Fighting : State::Walking;
    if (m_state == State::Walking)
        m_shape.move(sec * m_velocity * static_cast<float>(m_dir), 0.0f);
    else
        attack(sec);
    m_healthBar.update(m_shape.getPosition(), m_health/m_maxHealth);
}
void Soldier::takeDamage(float amount) {
    m_health -= amount;
}

sf::FloatRect Soldier::getAttackBounds() const {
    sf::FloatRect b = m_shape.getGlobalBounds();
    b.width += m_attackRange;
    if (m_team == Away)
        b.left -= m_attackRange;
    return b;
}

bool Soldier::hasValidTarget() const {
    if (!m_target.expired() && getAttackBounds().intersects(m_target.lock()->getBounds()))
        return true;
    return false;
}

void Soldier::setTarget(const std::weak_ptr<IDamageable>& target) {
    m_target = target;
}

void Soldier::clearTarget() {
    m_target = std::shared_ptr<IDamageable>();
}

void Soldier::attack(float dt) const {
    if (!m_target.expired())
        m_target.lock()->takeDamage(m_power*dt);
}

float Soldier::soldierPrice(Type soldierType) {
    switch (soldierType) {
        case Cow:
            return 5.0f;
        case Goat:
            return 3.0f;
        case Chicken:
            return 2.0f;
    }
    return 0;
}
