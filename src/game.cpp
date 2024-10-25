#include "game.hpp"

#include <cstring>
#include <iostream>

Game::Game()
    : m_players{sf::Color::Red, sf::Color::Blue}, m_playersTurn(0), m_board{0},
      m_state(Gamestate::Running)
{
    const char *fontPath = "/usr/share/fonts/truetype/DejaVuSans.ttf";

    if (!m_font.loadFromFile(fontPath))
    {
        std::cerr << "Failed to load font from '" << fontPath << "'"
                  << std::endl;
    }
}

void Game::render(sf::RenderWindow &win, int width, int height)
{
    int fieldWidth = width / 3;
    int fieldHeight = height / 3;

    sf::RectangleShape vertLine(sf::Vector2f(2, height));
    vertLine.setFillColor(sf::Color::Black);
    sf::RectangleShape horLine(sf::Vector2f(width, 2));
    horLine.setFillColor(sf::Color::Black);

    for (int i = 1; i < 3; i++)
    {
        vertLine.setPosition(i * fieldWidth, 0);
        win.draw(vertLine);
        horLine.setPosition(0, i * fieldHeight);
        win.draw(horLine);
    }

    for (int i = 0; i < 9; i++)
    {
        if (m_board[i] == 1)
        {
            sf::CircleShape circle(fieldWidth / 3);

            auto col = m_players[0].getColor();

            circle.setFillColor(col);
            circle.setOrigin(circle.getRadius(), circle.getRadius());
            circle.setPosition((i % 3) * fieldWidth + fieldWidth / 2,
                               (i / 3) * fieldHeight + fieldHeight / 2);

            // if fading, make it transparent
            if (i == m_players[0].getFadingPosition())
                circle.setFillColor(col * sf::Color(255, 255, 255, 128));

            win.draw(circle);
        }
        else if (m_board[i] == 2)
        {
            sf::RectangleShape cross(sf::Vector2f(fieldWidth / 3, fieldHeight));

            auto col = m_players[1].getColor();

            cross.setFillColor(col);
            cross.setOrigin(cross.getSize().x / 2, cross.getSize().y / 2);
            cross.setPosition((i % 3) * fieldWidth + fieldWidth / 2,
                              (i / 3) * fieldHeight + fieldHeight / 2);

            // if fading, make it transparent
            if (i == m_players[1].getFadingPosition())
                cross.setFillColor(col * sf::Color(255, 255, 255, 128));

            cross.rotate(45);
            win.draw(cross);

            // draw two half pieces, so the middle isn't drawn twice
            // otherwise transparency will not work correctly
            cross.setSize(sf::Vector2f(fieldWidth / 3, fieldHeight / 3));
            cross.rotate(90);
            win.draw(cross);
            cross.rotate(180);
            win.draw(cross);
        }
    }

    if (m_state == Gamestate::Player1Won)
    {
        sf::Text text("Player 1 won!", m_font, 30);
        text.setFillColor(sf::Color::Black);
        text.setPosition(width / 2 - text.getGlobalBounds().width / 2,
                         height / 2 - text.getGlobalBounds().height / 2);
        win.draw(text);
    }
    else if (m_state == Gamestate::Player2Won)
    {
        sf::Text text("Player 2 won!", m_font, 30);
        text.setFillColor(sf::Color::Black);
        text.setPosition(width / 2 - text.getGlobalBounds().width / 2,
                         height / 2 - text.getGlobalBounds().height / 2);
        win.draw(text);
    }
    else if (m_state == Gamestate::Draw)
    {
        sf::Text text("Draw!", m_font, 30);
        text.setFillColor(sf::Color::Black);
        text.setPosition(width / 2 - text.getGlobalBounds().width / 2,
                         height / 2 - text.getGlobalBounds().height / 2);
        win.draw(text);
    }

    if (m_state != Gamestate::Running)
    {
        sf::Text text2("Press Space to restart", m_font, 30);

        text2.setFillColor(sf::Color::Black);
        text2.setPosition(width / 2 - text2.getGlobalBounds().width / 2,
                          height / 2 - text2.getGlobalBounds().height / 2 - 30);
        win.draw(text2);
    }
}

bool Game::placeTile(int pos)
{
    if (m_board[pos] != 0 || m_state != Gamestate::Running)
        return false;

    m_players[m_playersTurn].placeTile(pos);
    updateBoard();
    m_playersTurn = (m_playersTurn + 1) % 2;

    int win = checkWin();

    if (win == 1)
        m_state = Gamestate::Player1Won;
    else if (win == 2)
        m_state = Gamestate::Player2Won;

    return true;
}

void Game::resetGame()
{
    if (m_state != Gamestate::Running)
    {
        m_players[0] = Player(sf::Color::Red);
        m_players[1] = Player(sf::Color::Blue);

        memset(m_board, 0, sizeof(m_board));

        m_playersTurn = 0;
        m_state = Gamestate::Running;
    }
}

void Game::updateBoard()
{
    for (int i = 0; i < 9; i++)
        m_board[i] = 0;

    const int *p1 = m_players[0].getPositions();
    const int *p2 = m_players[1].getPositions();

    for (int i = 0; i < 3; i++)
    {
        if (p1[i] != -1)
            m_board[p1[i]] = 1;
        if (p2[i] != -1)
            m_board[p2[i]] = 2;
    }
}

int Game::checkWin()
{
    int win = 0;

    // checking all verticals
    for (int i = 0; i < 3; i++)
    {
        if (m_board[i] != 0 && m_board[i] == m_board[i + 3] &&
            m_board[i] == m_board[i + 6])
            win = m_board[i];
    }

    // checking all horizontals
    for (int i = 0; i < 9; i += 3)
    {
        if (m_board[i] != 0 && m_board[i] == m_board[i + 1] &&
            m_board[i] == m_board[i + 2])
            win = m_board[i];
    }

    // diagonal checks
    if (m_board[0] != 0 && m_board[0] == m_board[4] && m_board[0] == m_board[8])
        win = m_board[0];

    if (m_board[2] != 0 && m_board[2] == m_board[4] && m_board[2] == m_board[6])
        win = m_board[2];

    return win;
}
