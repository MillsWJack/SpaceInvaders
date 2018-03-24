#pragma once
#include <SFML\Graphics.hpp>
class Alien
{
public:
	Alien(sf::Vector2f position, sf::Vector2f size);
	~Alien();

	void Render(sf::RenderWindow* window);

private:
	sf::Vector2f m_position;
	sf::Vector2f m_size;
	sf::RectangleShape m_rect;
};

