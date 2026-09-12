#pragma once
#include <SFML/Graphics/Rect.hpp>

class IDamageable {
public:
    enum Team { Home, Away };

    virtual ~IDamageable() = default;
    virtual void takeDamage(float amount) = 0;
    virtual sf::FloatRect getBounds() const = 0;
    virtual Team getTeam() const = 0;
    virtual bool isAlive() const = 0;
};
