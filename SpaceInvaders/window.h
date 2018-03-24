#pragma once
#include <SFML\Graphics.hpp>
#include <string>

#include <iostream>

class window
{
public:
	window(const sf::Vector2u& windowSize, const std::string& title);
	~window();

	sf::RenderWindow* GetRenderWindow() { return &m_window; }

	void Create();
	void Destroy();

	void BeginDraw();
	void Render(sf::Drawable& drawable);
	void EndDraw();

	void SetDone(bool set) { m_isDone = set; }

	bool isDone() { return m_isDone; }

private:
	bool m_isDone;

	sf::RenderWindow m_window;
	sf::Vector2u m_windowSize;
	std::string m_title;

};

