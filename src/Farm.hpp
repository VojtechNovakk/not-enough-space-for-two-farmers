#pragma once

#include <SFML/Graphics.hpp>
#include <optional>
#include "Soldier.hpp"
#include "HealthBar.hpp"
#include "IDamageable.hpp"

class Farm : public IDamageable{
    static constexpr float WIDTH = 80.f;
    static constexpr float HEIGHT = 96.f;
    static constexpr  float MAX_HEALTH = 500.0f;
    static constexpr unsigned int FONT_SIZE = 15;
    static constexpr float TEXT_OFFSET = 20.0f;
    static constexpr float SPAWN_COOLDOWN = 0.5f;
private:
    Team m_team;
    int m_level;
    float m_health;
    float m_money = 0.0f;
    float m_moneySpeed = 1.0f;
    float m_delay = 0.0f;
    sf::RectangleShape m_shape;
    sf::Sprite m_sprite;
    sf::Text m_moneyText;
    HealthBar m_healthBar;
public:
    Farm(bool home, const sf::Vector2u& winSize, const sf::Font& font, const sf::Texture& texture);
    void draw(sf::RenderWindow& window) const;
    std::optional<Soldier> spawnSoldier(Soldier::Type type);

    Team getTeam() const override;
    sf::FloatRect getBounds() const override { return m_shape.getGlobalBounds(); }
    void takeDamage(float amount) override;
    bool isAlive() const override { return m_health > 0.0f; }

    void update(float dt);
    void reset();
};