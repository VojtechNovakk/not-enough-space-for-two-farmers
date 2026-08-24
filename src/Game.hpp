#include <SFML/Graphics.hpp>
#include <string>

class Game {
private:
    sf::RenderWindow m_window;

    void processEvent();
public:
    Game(const int width, const int height, const std::string& title) : m_window(sf::VideoMode(width, height), title) {};
    void run();
};