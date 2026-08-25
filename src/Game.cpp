#include "Game.hpp"

void Game::run() {
    while (m_window.isOpen()) {
        processEvent();
        m_window.clear();
        for (Soldier& soldier : m_soldiers) {
            soldier.update();
            soldier.draw(m_window);
        }
        m_window.display();
    }
}

void Game::processEvent() {
    sf::Event event;
    while (m_window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            m_window.close();
        }
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Space) {
                Soldier new_soldier(Soldier::Type::Cow, 1, 10, 30, 0.0, m_height-30);
                m_soldiers.push_back(new_soldier);
            }
        }
    }
}
