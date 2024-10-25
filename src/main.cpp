#include <SFML/Graphics.hpp>

#include "game.hpp"

constexpr int WIDTH = 400;
constexpr int HEIGHT = 400;

void processEvent(const sf::Event &ev, Game &game, int width, int height)
{
    if (ev.mouseButton.button == sf::Mouse::Left)
    {
        int fieldWidth = width / 3;
        int fieldHeight = height / 3;

        int x = ev.mouseButton.x / fieldWidth;
        int y = ev.mouseButton.y / fieldHeight;

        game.placeTile(x + y * 3);
    }
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT),
                            "Tictactoc",
                            sf::Style::Titlebar | sf::Style::Close);

    window.setFramerateLimit(30);

    Game game;

    while (window.isOpen())
    {

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed)
                processEvent(event, game, WIDTH, HEIGHT);
            else if (event.type == sf::Event::KeyPressed &&
                     event.key.code == sf::Keyboard::Space)
                game.resetGame();
        }

        window.clear(sf::Color::White);
        game.render(window, WIDTH, HEIGHT);
        window.display();
    }

    return 0;
}
