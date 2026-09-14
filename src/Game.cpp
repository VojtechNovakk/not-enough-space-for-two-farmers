#include "Game.hpp"
#include <algorithm>
#include <SFML/Graphics.hpp>
#include <stdexcept>

static constexpr float MAX_DELTA = 0.05f;

Game::Game(const int width, const int height, const std::string& title) : m_window(sf::VideoMode(width, height), title), m_font(loadFont("assets/fonts/PressStart2P-Regular.ttf")),
m_farmTexture(loadTexture("assets/textures/farm.png")), m_menu(m_window.getSize(), m_font), m_endScreen(m_window.getSize(), m_font) {
    m_homeFarm = std::make_shared<Farm>(true, sf::Vector2u(width, height), m_font, m_farmTexture);
    m_awayFarm = std::make_shared<Farm>(false, sf::Vector2u(width, height), m_font, m_farmTexture);

    m_bgTexture.loadFromFile("assets/textures/bg.png");
    m_background.setTexture(m_bgTexture);
}

sf::Font Game::loadFont(const std::string &path) {
    sf::Font f;
    if (!f.loadFromFile(path))
        throw std::runtime_error("Nepovedlo se načíst font!");
    return f;
}

sf::Texture Game::loadTexture(const std::string &path) {
    sf::Texture t;
    if (!t.loadFromFile(path))
        throw std::runtime_error("Nepovedlo se načíst font!");
    return t;
}

void Game::run() {
    while (m_window.isOpen()) {
        if (m_state == State::Menu) {
            processEvent();
            m_window.clear();
            m_menu.draw(m_window);
        }else if (m_state == State::Playing) {
            sf::Time time = m_clock.restart();
            float dt = std::min(time.asSeconds(), MAX_DELTA);
            processEvent();
            for (auto& soldier : m_soldiers)
                soldier->update(dt);
            erase_if(m_soldiers, [](const std::shared_ptr<Soldier>& soldier){ return !(soldier->isAlive()); });
            m_homeFarm->update(dt);
            m_awayFarm->update(dt);
            if (!m_homeFarm->isAlive())
                endGame(Winner::Away);
            else if (!m_awayFarm->isAlive())
                endGame(Winner::Home);
            handleCollisions();

            m_window.clear();

            m_window.draw(m_background);
            for (const auto& soldier : m_soldiers)
                soldier->draw(m_window);
            m_homeFarm->draw(m_window);
            m_awayFarm->draw(m_window);
        }else {
            processEvent();
            m_window.clear();
            m_endScreen.draw(m_window);
        }

        m_window.display();
    }
}

void Game::startGame() {
    m_soldiers.clear();
    m_homeFarm->reset();
    m_awayFarm->reset();
    m_clock.restart();
    m_state = State::Playing;
}

void Game::endGame(Winner winner) {
    m_state = State::GameOver;
    if (winner == Winner::Home)
        m_endScreen.setWinner("Winner is player1!");
    else if (winner == Winner::Away)
        m_endScreen.setWinner("Winner is player2!");
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
        if (m_state == State::Menu) {
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Space)
                    startGame();
            }
        }else if (m_state == State::Playing) {
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Q) {
                    if (std::optional<Soldier> s = m_homeFarm->spawnSoldier(Soldier::Type::Cow))
                        m_soldiers.push_back(std::make_shared<Soldier>(std::move(*s)));
                }
                if (event.key.code == sf::Keyboard::W) {
                    if (std::optional<Soldier> s = m_homeFarm->spawnSoldier(Soldier::Type::Goat))
                        m_soldiers.push_back(std::make_shared<Soldier>(std::move(*s)));
                }
                if (event.key.code == sf::Keyboard::E) {
                    if (std::optional<Soldier> s = m_homeFarm->spawnSoldier(Soldier::Type::Chicken))
                        m_soldiers.push_back(std::make_shared<Soldier>(std::move(*s)));
                }
                if (event.key.code == sf::Keyboard::Left) {
                    if (std::optional<Soldier> s = m_awayFarm->spawnSoldier(Soldier::Type::Cow))
                        m_soldiers.push_back(std::make_shared<Soldier>(std::move(*s)));
                }
                if (event.key.code == sf::Keyboard::Down) {
                    if (std::optional<Soldier> s = m_awayFarm->spawnSoldier(Soldier::Type::Goat))
                        m_soldiers.push_back(std::make_shared<Soldier>(std::move(*s)));
                }
                if (event.key.code == sf::Keyboard::Right) {
                    if (std::optional<Soldier> s = m_awayFarm->spawnSoldier(Soldier::Type::Chicken))
                        m_soldiers.push_back(std::make_shared<Soldier>(std::move(*s)));
                }
            }
        }else {
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::R)
                    m_state = State::Menu;
            }
        }
    }
}
