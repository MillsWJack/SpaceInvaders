#pragma once

#include <SFML\Graphics.hpp>
#include <iostream>

class Score
{
public:
	Score(unsigned int size = 24, sf::Color color = sf::Color::White);
	~Score();

	void DrawText(const std::string& text, const sf::Vector2f& position);
	void Render(sf::RenderWindow& window);

private:

	sf::Font m_font;
	sf::Text m_text;
	sf::Color m_color;
	
	unsigned int m_size;
};

