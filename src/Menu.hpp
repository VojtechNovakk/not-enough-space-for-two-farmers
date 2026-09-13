#pragma once

#include <SFML/Graphics.hpp>

class Menu {
public:
    static constexpr float W_SIZE= 300.0f;
    static constexpr float H_SIZE= 90.0f;
    static constexpr unsigned int FONT_SIZE = 15;
private:
    sf::RectangleShape m_button;
    sf::Font m_font;
    sf::Text m_buttonText;
public:
    Menu(const sf::Vector2u& winSize);

    void draw(sf::RenderWindow& window) const;
};