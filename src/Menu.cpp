#include "Menu.hpp"
#include <stdexcept>

Menu::Menu(const sf::Vector2u& winSize) : m_button(sf::Vector2f(W_SIZE, H_SIZE)){
    m_button.setFillColor(sf::Color::White);
    m_button.setPosition(winSize.x/2 - W_SIZE/2, winSize.y/2 - H_SIZE/2);

    if (!m_font.loadFromFile("assets/fonts/PressStart2P-Regular.ttf"))
        throw std::runtime_error("Nepovedlo se načíst font!");
    m_buttonText.setString("Press SPACE");
    m_buttonText.setFillColor(sf::Color::Black);
    m_buttonText.setCharacterSize(FONT_SIZE);
    m_buttonText.setFont(m_font);
    sf::FloatRect scale = m_buttonText.getGlobalBounds();
    m_buttonText.setPosition(winSize.x/2 - scale.width/2, winSize.y/2- scale.height/2);
}

void Menu::draw(sf::RenderWindow &window) const {
    window.draw(m_button);
    window.draw(m_buttonText);
}
