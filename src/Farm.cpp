#include "Farm.hpp"

#include "IDamageable.hpp"
#include <algorithm>
#include <string>

Farm::Farm(bool home, const sf::Vector2u& winSize, const sf::Font& font, const sf::Texture& texture) : m_team(home ? Team::Home : Team::Away), m_level(1),
m_health(MAX_HEALTH), m_shape(sf::Vector2f(WIDTH, HEIGHT)), m_healthBar(WIDTH, m_team == Team::Home ? HealthBar::Anchor::Left : HealthBar::Anchor::Right), m_sprite(texture){
    if (home)
        m_shape.setPosition(0.0f, static_cast<float>(winSize.y) - HEIGHT);
    else
        m_shape.setPosition(static_cast<float>(winSize.x) - WIDTH, static_cast<float>(winSize.y) - HEIGHT);
    m_shape.setFillColor(sf::Color::Red);
    m_moneyText.setFont(font);
    m_moneyText.setFillColor(sf::Color::White);
    m_moneyText.setCharacterSize(FONT_SIZE);
    if (m_team == Team::Home) {
        m_moneyText.setPosition(TEXT_OFFSET, TEXT_OFFSET);
        m_sprite.setOrigin(0.0f, HEIGHT);
        m_sprite.setPosition(0.0f, winSize.y);
    }
    else {
        m_moneyText.setPosition(winSize.x - TEXT_OFFSET, TEXT_OFFSET);
        m_sprite.setOrigin(WIDTH, HEIGHT);
        m_sprite.setPosition(winSize.x, winSize.y);
    }
}

std::optional<Soldier> Farm::spawnSoldier(Soldier::Type type) {
    float soldierPrice = Soldier::soldierPrice(type);
    if (m_money < soldierPrice || m_delay > 0.0f)
        return std::nullopt;
    m_money -= soldierPrice;
    m_delay = SPAWN_COOLDOWN;
    sf::Vector2f farmPos = m_shape.getPosition();
    return Soldier(type, m_team, m_level, 15.0f, 40.0f, m_team == Team::Home ? farmPos.x+30.0f : farmPos.x+WIDTH-30.0f, farmPos.y+HEIGHT-40.0f);
}

void Farm::draw(sf::RenderWindow& window) const {
    window.draw(m_sprite);
    window.draw(m_moneyText);
    m_healthBar.draw(window);
}

Farm::Team Farm::getTeam() const { return m_team; }

void Farm::takeDamage(float amount) {
    m_health -= amount;
}

void Farm::update(float dt) {
    m_delay = std::max(m_delay - dt, 0.0f);
    m_healthBar.update(m_shape.getPosition(), m_health / MAX_HEALTH);
    m_money += m_moneySpeed * dt;
    m_moneyText.setString(std::to_string(static_cast<int>(m_money)));
    if (m_team == Team::Away) {
        sf::FloatRect b = m_moneyText.getLocalBounds();
        m_moneyText.setOrigin(b.left+b.width, b.top);
    }
}

void Farm::reset() {
    m_health = MAX_HEALTH;
    m_money = 0.0f;
    m_delay = 0.0f;
}
