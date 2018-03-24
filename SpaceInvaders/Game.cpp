#include "Game.h"

Game::Game():
	m_window(sf::Vector2u(800, 600), "Window"),
	m_player(sf::Vector2f(800 / 2, 500), sf::Vector2f(100, 25), 5)
{
}

Game::~Game()
{
}

void Game::HandleInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		m_player.MoveLeft();
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		m_player.MoveRight();
	}
}

void Game::Update()
{
	sf::Event event;
	while (m_window.GetRenderWindow()->pollEvent(event))
	{
		if (event.type == sf::Event::Closed ||
			sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			m_window.SetDone(true);
		}
		if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Up)
		{
			Bullet* bullet = new Bullet(sf::Vector2f(4, 10), m_player.GetPosition());
			m_bulletList.push_back(bullet);
			std::cout << "Bullet added.\n";
			std::cout << m_bulletList.size() << std::endl;
		}
	}

	m_player.Update();
	
	for (std::vector<Bullet*>::iterator iter = m_bulletList.begin(); iter != m_bulletList.end();)
	{
		if ((*iter)->GetPosition().y < 0)
		{
			iter = m_bulletList.erase(iter);
		}
		else
		{
			(*iter)->Update();
			iter++;
		}
	}
}

void Game::Render()
{
	m_window.BeginDraw();

	m_player.Render(*(m_window.GetRenderWindow()));
	
	for (std::vector<Bullet*>::iterator iter = m_bulletList.begin(); iter != m_bulletList.end(); iter++)
	{
		(*iter)->Render(*(m_window.GetRenderWindow()));
	}

	m_window.EndDraw();
}