#include "Player.h"

Player::Player(sf::Vector2f position, sf::Vector2f size, float speed):
	m_position(position),
	m_size(size),
	m_moveSpeed(speed)
{
	m_rect.setSize(m_size);
}

Player::~Player()
{
}

void Player::MoveLeft()
{
	if (m_position.x <= 0)
	{
		m_position.x = 0;
	}
	else 
	{
		m_position.x -= m_moveSpeed;
	}
}

void Player::MoveRight()
{
	if (m_position.x + m_size.x >= 1920)
	{
		m_position.x = 1920 - m_size.x;
	}
	else
	{
		m_position.x += m_moveSpeed;
	}
}

void Player::Render(sf::RenderWindow& window)
{
	m_rect.setPosition(m_position.x, m_position.y);
	m_rect.setFillColor(sf::Color::Green);
	window.draw(m_rect);
}

void Player::Update()
{
}