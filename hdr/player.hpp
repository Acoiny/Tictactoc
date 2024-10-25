#pragma once

#include <SFML/Graphics.hpp>

class Player
{
  public:
    Player(const sf::Color &col);
    ~Player() = default;

    void placeTile(int pos);

    const int *getPositions() const { return m_positions; }
    int getFadingPosition() const { return m_positions[m_active]; }

    const sf::Color &getColor() const { return m_color; }

  private:
    int m_positions[3];
    int m_active;
    sf::Color m_color;
};