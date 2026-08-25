#include "Game.hpp"

void Game::run() {
    while (m_window.isOpen()) {
        sf::Time time = m_clock.restart();
        processEvent();
        m_window.clear();
        m_homeFarm.update(time.asSeconds());
        m_awayFarm.update(time.asSeconds());
        m_homeFarm.draw(m_window);
        m_awayFarm.draw(m_window);
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
            if (event.key.code == sf::Keyboard::Space)
                m_homeFarm.addSoldier(Soldier::Type::Cow);
            if (event.key.code == sf::Keyboard::Enter)
                m_awayFarm.addSoldier(Soldier::Type::Cow);
        }
    }
}
