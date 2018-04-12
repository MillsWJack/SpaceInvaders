#include "Score.h"

Score::Score(unsigned int size, sf::Color color):
	m_size(size),
	m_color(color)
{
	if (!m_font.loadFromFile("JackPixel.ttf"))
	{
		std::cout << "Failed to load font from file.\n";
	}

	m_text.setFont(m_font);
	m_text.setCharacterSize(m_size);
	m_text.setFillColor(m_color);
}

Score::~Score()
{
}

void Score::DrawText(const std::string& text, const sf::Vector2f& position)
{
	m_text.setString(text);
	m_text.setPosition(position);
}

void Score::Render(sf::RenderWindow& window)
{
	window.draw(m_text);
}