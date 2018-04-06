#pragma once
#include <SFML\Graphics.hpp>

class Alien
{
public:
	Alien(sf::Vector2f position, sf::Vector2f size, int sprite = 0);
	~Alien();

	void Render(sf::RenderWindow& window);

	void Move();
	void ShiftDown();
	void InvertDir();
	void SetSpriteRect();


	sf::Vector2f& GetPosition() { return m_position; }
	sf::Vector2f& GetSize() { return m_size; }
	int GetMoveDir() { return m_moveDir; }

	void SetMoveSpeed(float setter) { m_moveSpeed += setter; }

private:
	sf::Vector2f m_position;
	sf::Vector2f m_size;

	sf::Texture m_texture;
	sf::Sprite m_sprite;
	sf::Image m_image;

	int m_moveDir;
	int m_frame;
	int m_alienType;
	float m_moveSpeed;
};

