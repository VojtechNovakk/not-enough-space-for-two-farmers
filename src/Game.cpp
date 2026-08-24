#include "Game.hpp"

void Game::run() {
    while (m_window.isOpen()) {
        processEvent();
        m_window.clear();
        m_window.display();
    }
}

void Game::processEvent() {
    sf::Event event;
    while (m_window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            m_window.close();
        }
    }
}
