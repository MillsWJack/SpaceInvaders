#include "Alien.h"

Alien::Alien(sf::Vector2f position, sf::Vector2f size):
	m_position(position),
	m_size(size)
{
	m_rect.setSize(m_size);
}

Alien::~Alien()
{
}

void Alien::Render(sf::RenderWindow* window)
{
	m_rect.setPosition(m_position);
	window->draw(m_rect);
}