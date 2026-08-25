#include "Farm.hpp"

Farm::Farm(bool home, const sf::Vector2u& winSize) : m_home(home), m_level(1), m_health(100), m_money(0), m_shape(sf::Vector2f(SIZE, SIZE)) {
    if (home)
        m_shape.setPosition(0.0f, static_cast<float>(winSize.y) - SIZE);
    else
        m_shape.setPosition(static_cast<float>(winSize.x) - SIZE, static_cast<float>(winSize.y) - SIZE);
    m_shape.setFillColor(sf::Color::Red);
}
void Farm::update(float sec) {
   for (Soldier& soldier: m_soldiers)
       soldier.update(sec);
}
void Farm::draw(sf::RenderWindow& window) const {
    window.draw(m_shape);
    for (const Soldier& soldier : m_soldiers) {
        soldier.draw(window);
    }
}
void Farm::addSoldier(Soldier::Type type) {
    sf::Vector2f farmPos = m_shape.getPosition();
    m_soldiers.emplace_back(type, m_level, 15.0f, 40.0f, m_home ? 1 : -1, m_home ? farmPos.x+30.0f : farmPos.x+SIZE-30.0f, farmPos.y+SIZE-40.0f);
}