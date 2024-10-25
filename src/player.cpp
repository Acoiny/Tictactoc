#include "player.hpp"

Player::Player(const sf::Color &col)
    : m_positions{-1, -1, -1}, m_active(0), m_color(col)
{
}

void Player::placeTile(int pos)
{
    m_positions[m_active] = pos;
    m_active = (m_active + 1) % 3;
}
