#pragma once

#include <SFML/Graphics.hpp>

class HealthBar {
    static constexpr  float BAR_HEIGHT = 5.0f;
    static constexpr  float BAR_OFFSET = 10.0f;
public:
    enum Anchor {
        Left,
        Right
    };
private:
    float m_width;
    sf::RectangleShape m_shape;
    Anchor m_anchor;
public:
    HealthBar(float width, Anchor anchor);
    void updateHealthBar(float healthPercentage);
    void draw(sf::RenderWindow& window) const;
    void update(const sf::Vector2f& position, float percentageHealth);
};