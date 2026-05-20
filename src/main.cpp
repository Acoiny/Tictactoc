#include <SFML/Graphics.hpp>
#include <SFML/Window/VideoMode.hpp>

#include "game.hpp"

constexpr int WIDTH = 400;
constexpr int HEIGHT = 400;

void processEvent(const sf::Event::MouseButtonPressed &event, Game &game,
                  int width, int height)
{
    int fieldWidth = width / 3;
    int fieldHeight = height / 3;

    int x = event.position.x / fieldWidth;
    int y = event.position.y / fieldHeight;

    game.placeTile(x + y * 3);
}

int main()
{
    sf::RenderWindow window(sf::VideoMode({WIDTH, HEIGHT}), "Tictactoc",
                            sf::Style::Titlebar | sf::Style::Close);

    window.setFramerateLimit(30);

    Game game;

    while (window.isOpen())
    {

        while (auto ev = window.pollEvent())
        {
            if (ev->is<sf::Event::Closed>())
                window.close();

            if (auto event = ev->getIf<sf::Event::MouseButtonPressed>())
                processEvent(*event, game, WIDTH, HEIGHT);
            else if (auto event = ev->getIf<sf::Event::KeyPressed>())
                if (event->code == sf::Keyboard::Key::Space)
                    game.resetGame();
        }

        window.clear(sf::Color::White);
        game.render(window, WIDTH, HEIGHT);
        window.display();
    }

    return 0;
}
