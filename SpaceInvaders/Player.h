#pragma once
#include <SFML\Graphics.hpp>
class Player
{
public:
	Player(sf::Vector2f position, sf::Vector2f size, float speed);
	~Player();

	void MoveLeft();
	void MoveRight();
	void Render(sf::RenderWindow& window);
	void Update();

	sf::Vector2f& GetPosition() { return m_position; }

private:
	sf::Vector2f m_position;
	sf::Vector2f m_size;
	sf::RectangleShape m_rect;

	float m_moveSpeed;
};

