#include "Player.h"

Player::Player(sf::Vector2f position, float speed):
	m_position(position),
	m_moveSpeed(speed)
{
	m_image.loadFromFile("ship.png");
	m_image.createMaskFromColor(sf::Color::Black);
	m_texture.loadFromImage(m_image);
	m_sprite.setTexture(m_texture);
	m_sprite.setTextureRect(sf::IntRect(20, 95, 249, 153));
	m_sprite.setOrigin(124, 76);
	m_sprite.setScale(0.5, 0.5);
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
	m_sprite.setPosition(m_position);
	window.draw(m_sprite);
}

void Player::Update()
{
}