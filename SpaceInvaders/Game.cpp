#include "Game.h"

Game::Game():
	m_window(sf::Vector2u(800, 600), "Window"),
	m_player(sf::Vector2f(800 / 2, 500), sf::Vector2f(100, 25), 5)
{
	for (int j = 1; j < 2; j++)
	{
		for (int i = 1; i < 13; i++)
		{
			Alien* alien = new Alien(sf::Vector2f(i * 58, j * 50), sf::Vector2f(40, 40));
			m_alienList.push_back(alien);
		}
	}
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

	for (std::vector<Alien*>::iterator alienIter = m_alienList.begin(); alienIter != m_alienList.end();)
	{
		for (std::vector<Bullet*>::iterator bulletIter = m_bulletList.begin(); bulletIter != m_bulletList.end();)
		{
			if (HasCollided((*bulletIter), (*alienIter)))
			{
				(*alienIter)->SetVisibility(false);

				//Pop affected alien and bullet from heap
				alienIter = m_alienList.erase(alienIter);
				bulletIter = m_bulletList.erase(bulletIter);

				std::cout << "Alien removed.\n";
				std::cout << m_alienList.size() << std::endl;
			}
			else
			{
				bulletIter++;
			}
		}
		if (m_alienList.size() != 0)
		{
			alienIter++;
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
	for (std::vector<Alien*>::iterator iter = m_alienList.begin(); iter != m_alienList.end(); iter++)
	{
		if ((*iter)->IsVisible())
		{
			(*iter)->Render(*(m_window.GetRenderWindow()));
		}
	}

	m_window.EndDraw();
}

bool Game::HasCollided(Bullet* bullet, Alien* alien)
{
	if (bullet->GetPosition().y <= alien->GetPosition().y + alien->GetSize().y &&
		bullet->GetPosition().x >= alien->GetPosition().x &&
		bullet->GetPosition().x <= alien->GetPosition().x + alien->GetSize().x)
	{
		return true;
	}

	return false;
}