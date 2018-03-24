#include "window.h"

window::window(const sf::Vector2u& windowSize, const std::string& title):
	m_windowSize(windowSize),
	m_title(title)
{
	Create();
}

window::~window()
{
}

void window::Create()
{
	m_window.create({ m_windowSize.x, m_windowSize.y }, m_title);
	m_window.setFramerateLimit(60);
}

void window::Destroy()
{
	m_window.close();
}

void window::BeginDraw()
{
	m_window.clear(sf::Color::Black);
}

void window::Render(sf::Drawable& drawable)
{
	m_window.draw(drawable);
}

void window::EndDraw()
{
	m_window.display();
}