#pragma once

#include <SFML/Graphics.hpp>
#include "HealthBar.hpp"
#include "IDamageable.hpp"
#include <memory>

class Soldier : public IDamageable {
public:
    enum Type { Cow, Goat, Chicken };
    enum State { Walking, Fighting };
private:
    Type m_type;
    Team m_team;
    State m_state;
    float m_maxHealth;
    float m_health;
    int m_level;
    float m_velocity;
    int m_dir;
    float m_power;
    float m_attackRange;
    sf::RectangleShape m_shape;
    HealthBar m_healthBar;
    std::weak_ptr<IDamageable> m_target;

public:
    Soldier(Type type, Team team, int level, float width, float height, float x, float y);

    void draw(sf::RenderWindow &window) const;
    void update(float sec);

    sf::FloatRect getBounds() const override { return m_shape.getGlobalBounds(); }
    sf::FloatRect getAttackBounds() const;
    Team getTeam() const override { return m_team; }
    float getHealth() const { return m_health; }

    void takeDamage(float amount) override;
    bool isAlive() const override { return m_health > 0.0f; }

    bool hasValidTarget() const;
    void setTarget(const std::weak_ptr<IDamageable>& target);
    void clearTarget();
    void attack(float dt) const;

    static float soldierPrice(Type soldierType);
};
