#pragma once
#include <SFML\Graphics.hpp>
class Bullet
{
public:
	Bullet(sf::Vector2f size, sf::Vector2f position);
	~Bullet();

	void Update();
	void Render(sf::RenderWindow& window);

	void ToggleIsShot() { m_isShot = !m_isShot; }

	sf::Vector2f& GetPosition() { return m_position; }
	bool IsShot() { return m_isShot; }

private:
	sf::Vector2f m_size;
	sf::Vector2f m_position;
	sf::RectangleShape m_rect;

	bool m_isShot;
};

