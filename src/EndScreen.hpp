#pragma once

#include <SFML/Graphics.hpp>
#include <string>

class EndScreen {
public:
    static constexpr unsigned int FONT_SIZE_WINNER = 15;
    static constexpr unsigned int FONT_SIZE_RESET = 8;
    static constexpr float OFFSET = 120.0f;
private:
    sf::Font m_font;
    sf::Text m_winnerText;
    sf::Text m_resetText;
public:
    EndScreen(const sf::Vector2u& winSize);
    void draw(sf::RenderWindow& window) const;
    void setWinner(const std::string& winnerString);
    static void fixTextOrigin(sf::Text& text);
};