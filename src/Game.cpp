#include "Game.hpp"
#include <algorithm>

static constexpr float MAX_DELTA = 0.05f;

void Game::run() {
    while (m_window.isOpen()) {
        sf::Time time = m_clock.restart();
        float dt = std::min(time.asSeconds(), MAX_DELTA);
        processEvent();
        for (auto& soldier : m_soldiers)
            soldier->update(dt);
        erase_if(m_soldiers, [](const std::shared_ptr<Soldier>& soldier){ return !(soldier->isAlive()); });
        m_homeFarm->update(dt);
        m_awayFarm->update(dt);
        handleCollisions();

        m_window.clear();

        m_homeFarm->draw(m_window);
        m_awayFarm->draw(m_window);
        for (const auto& soldier : m_soldiers)
            soldier->draw(m_window);

        m_window.display();
    }
}

void Game::handleCollisions() const {
    for (size_t i = 0; i < m_soldiers.size(); ++i) {
        if (m_soldiers[i]->hasValidTarget())
            continue;
        sf::FloatRect curBounds = m_soldiers[i]->getAttackBounds();
        std::weak_ptr<IDamageable> bestTarget;
        float targetDis = -1.0f;
        for (size_t j = 0; j < m_soldiers.size(); ++j) {
            if (m_soldiers[i]->getTeam() == m_soldiers[j]->getTeam())
                continue;
            if (curBounds.intersects(m_soldiers[j]->getBounds())) {
                if (m_soldiers[i]->getTeam() == Soldier::Team::Home) {
                    if (targetDis < 0.0f || m_soldiers[j]->getBounds().left < targetDis) {
                        targetDis = m_soldiers[j]->getBounds().left;
                        bestTarget = m_soldiers[j];
                    }
                }else {
                    if (targetDis < 0.0f || m_soldiers[j]->getBounds().left > targetDis) {
                        targetDis = m_soldiers[j]->getBounds().left;
                        bestTarget = m_soldiers[j];
                    }
                }
            }
        }
        if (bestTarget.expired()) {
            if (m_soldiers[i]->getTeam() == Soldier::Team::Home) {
                if (curBounds.intersects(m_awayFarm->getBounds()))
                    m_soldiers[i]->setTarget(m_awayFarm);
            }else {
                if (curBounds.intersects(m_homeFarm->getBounds()))
                    m_soldiers[i]->setTarget(m_homeFarm);
            }
        }else
            m_soldiers[i]->setTarget(bestTarget);
    }
}

void Game::processEvent() {
    sf::Event event;
    while (m_window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            m_window.close();
        }
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Q)
                m_soldiers.push_back(std::make_shared<Soldier>(m_homeFarm->spawnSoldier(Soldier::Type::Cow)));
            if (event.key.code == sf::Keyboard::W)
                m_soldiers.push_back(std::make_shared<Soldier>(m_homeFarm->spawnSoldier(Soldier::Type::Goat)));
            if (event.key.code == sf::Keyboard::E)
                m_soldiers.push_back(std::make_shared<Soldier>(m_homeFarm->spawnSoldier(Soldier::Type::Chicken)));
            if (event.key.code == sf::Keyboard::Left)
                m_soldiers.push_back(std::make_shared<Soldier>(m_awayFarm->spawnSoldier(Soldier::Type::Cow)));
            if (event.key.code == sf::Keyboard::Down)
                m_soldiers.push_back(std::make_shared<Soldier>(m_awayFarm->spawnSoldier(Soldier::Type::Goat)));
            if (event.key.code == sf::Keyboard::Right)
                m_soldiers.push_back(std::make_shared<Soldier>(m_awayFarm->spawnSoldier(Soldier::Type::Chicken)));
        }
    }
}
