#pragma once

#include "player.hpp"

#include <SFML/Graphics.hpp>

enum class Gamestate
{
    Running,
    Player1Won,
    Player2Won,
    Draw
};

class Game
{
  public:
    Game();
    ~Game() = default;

    void render(sf::RenderWindow& win, int width, int height);

    /// @brief Places a tile at the given position for te current player
    /// @param pos position on the board
    /// @return true if successful, false otherwise
    bool placeTile(int pos);

    void resetGame();

private:
    void updateBoard();

    int checkWin();

  private:
    sf::Font m_font;
    Player m_players[2];
    int m_playersTurn;
    int m_board[9];
    Gamestate m_state;
};
