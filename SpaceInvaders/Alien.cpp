#include "Alien.h"

Alien::Alien(sf::Vector2f position, int sprite):
	m_position(position),
	m_alienType(sprite)
{
	m_moveDir = 1;
	m_moveSpeed = 1;
	m_frame = 1;

	m_image.loadFromFile("aliens.png");
	m_image.createMaskFromColor(sf::Color::Black);
	
	m_texture.loadFromImage(m_image);
	m_sprite.setTexture(m_texture);
	
	//Set texture rect to portion of image that has desired alien
	SetSpriteRect();

	m_sprite.setPosition(m_position);
	m_size = m_sprite.getTextureRect();
}

Alien::~Alien()
{
}

void Alien::Render(sf::RenderWindow& window)
{
	m_sprite.setPosition(m_position);
	window.draw(m_sprite);
}

//Move based on current direction (- = left, + = right)
void Alien::Move() 
{
	m_position.x += (m_moveDir * m_moveSpeed);
	if ((int)m_position.x % 20 == 0)
	{
		m_frame *= -1;
	}
	SetSpriteRect();
}

//Shifts position down by amount
void Alien::ShiftDown()
{
	m_position.y += 40;
	SetMoveSpeed(0.3);
}

//Inverts current direction
void Alien::InvertDir() 
{
	m_moveDir *= -1;
}

void Alien::SetSpriteRect()
{
	switch (m_frame)
	{
	case -1:
		switch (m_alienType)
		{
		case 0:
			m_sprite.setTextureRect(sf::IntRect(27, 20, 46, 66));
			break;
		case 1:
			m_sprite.setTextureRect(sf::IntRect(18, 93, 62, 45));
			break;
		case 2:
			m_sprite.setTextureRect(sf::IntRect(9, 167, 68, 45));
			break;
		}
		break;
	case 1:
		switch (m_alienType)
		{
		case 0:
			m_sprite.setTextureRect(sf::IntRect(98, 20, 46, 66));
			break;
		case 1:
			m_sprite.setTextureRect(sf::IntRect(91, 93, 62, 45));
			break;
		case 2:
			m_sprite.setTextureRect(sf::IntRect(88, 167, 68, 45));
			break;
		}
	}
}