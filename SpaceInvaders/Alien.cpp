#include "Alien.h"

Alien::Alien(sf::Vector2f position, sf::Vector2f size):
	m_position(position),
	m_size(size)
{
	m_isVisible = true;
	m_rect.setSize(m_size);
	m_moveDir = 1;
}

Alien::~Alien()
{
}

void Alien::Render(sf::RenderWindow& window)
{
	m_rect.setPosition(m_position);
	m_rect.setFillColor(sf::Color::Green);
	window.draw(m_rect);
}

void Alien::Move() //Move based on current direction (- = left, + = right)
{
	m_position.x += m_moveDir;
}

void Alien::ShiftDown() //Shifts position down by amount
{
	m_position.y += 40;
}

void Alien::InvertDir() //Inverts current direction
{
	m_moveDir *= -1;
}