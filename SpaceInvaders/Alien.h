#pragma once
#include <SFML\Graphics.hpp>
class Alien
{
public:
	Alien(sf::Vector2f position, sf::Vector2f size);
	~Alien();

	void Render(sf::RenderWindow& window);

	void Move();
	void ShiftDown();
	void InvertDir();

	sf::Vector2f& GetPosition() { return m_position; }
	sf::Vector2f& GetSize() { return m_size; }

private:
	sf::Vector2f m_position;
	sf::Vector2f m_size;
	sf::RectangleShape m_rect;

	int m_moveDir;
};

