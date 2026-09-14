#include "EndScreen.hpp"

EndScreen::EndScreen(const sf::Vector2u& winSize, const sf::Font& font){
    m_winnerText.setFont(font);
    m_winnerText.setFillColor(sf::Color::White);
    m_winnerText.setCharacterSize(FONT_SIZE_WINNER);
    m_winnerText.setPosition(winSize.x/2.0f, winSize.y/2.0f);
    m_resetText.setFont(font);
    m_resetText.setFillColor(sf::Color::White);
    m_resetText.setCharacterSize(FONT_SIZE_RESET);
    m_resetText.setString("Press R for return to the Menu!");
    fixTextOrigin(m_resetText);
    m_resetText.setPosition(winSize.x/2.0f, winSize.y - OFFSET);
}

void EndScreen::draw(sf::RenderWindow& window) const {
    window.draw(m_winnerText);
    window.draw(m_resetText);
}

void EndScreen::setWinner(const std::string &winnerString) {
    m_winnerText.setString(winnerString);
    fixTextOrigin(m_winnerText);
}

void EndScreen::fixTextOrigin(sf::Text& text) {
    sf::FloatRect b = text.getLocalBounds();
    text.setOrigin(b.left + b.width / 2.0f, b.top + b.height / 2.0f);
}
