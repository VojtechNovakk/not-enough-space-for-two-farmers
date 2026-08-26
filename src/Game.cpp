#include "Game.hpp"
#include <algorithm>

static constexpr float MAX_DELTA = 0.05f;

void Game::run() {
    while (m_window.isOpen()) {
        sf::Time time = m_clock.restart();
        float dt = std::min(time.asSeconds(), MAX_DELTA);
        processEvent();
        for (Soldier& soldier : m_soldiers)
            soldier.update(dt);
        m_homeFarm.update(dt);
        m_awayFarm.update(dt);
        handleCollisions(dt);

        m_window.clear();

        m_homeFarm.draw(m_window);
        m_awayFarm.draw(m_window);
        for (const Soldier& soldier : m_soldiers)
            soldier.draw(m_window);

        m_window.display();
    }
}

void Game::handleCollisions(float dt) {
    for (size_t i = 0; i < m_soldiers.size(); ++i)
        m_soldiers[i].setState(Soldier::State::Walking);

    std::vector<std::pair<size_t, size_t>> targets;
    for (size_t i = 0; i < m_soldiers.size(); ++i) {
        sf::FloatRect curSoldierBounds = m_soldiers[i].getBounds();
        for (size_t j = 0; j < m_soldiers.size(); ++j) {
            if (m_soldiers[i].getTeam() != m_soldiers[j].getTeam() && curSoldierBounds.intersects(m_soldiers[j].getBounds())) {
                targets.emplace_back(i, j);
                break;
            }
        }
        if (m_soldiers[i].getTeam() == Soldier::Team::Home && curSoldierBounds.intersects(m_awayFarm.getBounds()))
            m_soldiers[i].setState(Soldier::State::Fighting);
        else if (m_soldiers[i].getTeam() == Soldier::Team::Away && curSoldierBounds.intersects(m_homeFarm.getBounds()))
            m_soldiers[i].setState(Soldier::State::Fighting);
    }
    for (size_t i = 0; i < targets.size(); ++i) {
        m_soldiers[targets[i].first].setState(Soldier::State::Fighting);
        m_soldiers[targets[i].second].takeDamage(m_soldiers[targets[i].first], dt);
    }
    std::erase_if(m_soldiers, [](const Soldier& s) {
        return s.getHealth() <= 0;
    });
}

void Game::processEvent() {
    sf::Event event;
    while (m_window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            m_window.close();
        }
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Space)
                m_soldiers.push_back(m_homeFarm.spawnSoldier(Soldier::Type::Cow));
            if (event.key.code == sf::Keyboard::Enter)
                m_soldiers.push_back(m_awayFarm.spawnSoldier(Soldier::Type::Cow));
        }
    }
}
