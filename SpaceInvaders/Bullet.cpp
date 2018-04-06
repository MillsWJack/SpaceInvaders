#include "Bullet.h"

Bullet::Bullet(sf::Vector2f size, sf::Vector2f position):
	m_size(size)
{
	m_position.x = position.x + 50;
	m_position.y = position.y;
	m_rect.setSize(m_size);
}


Bullet::~Bullet()
{
}

void Bullet::Render(sf::RenderWindow& window)
{
	m_rect.setPosition(m_position);
	m_rect.setFillColor(sf::Color::Green);
	window.draw(m_rect);
}

void Bullet::Update()
{
	m_position.y -= 15;
}