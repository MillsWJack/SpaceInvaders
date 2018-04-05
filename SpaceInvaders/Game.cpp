#include "Game.h"

Game::Game():
	m_window(sf::Vector2u(800, 600), "Window"),
	m_player(sf::Vector2f(800 / 2, 550), sf::Vector2f(100, 25), 5)
{
	for (int j = 1; j < row; j++)
	{
		for (int i = 1; i < col; i++)
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
		}
	}

	m_player.Update();

	//Move aliens based on positions
	MoveAliens();
	
	//Bullet cleanup if off the screen, otherwise update
	for (std::vector<Bullet*>::const_iterator iter = m_bulletList.begin(); iter != m_bulletList.end();)
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

	//Handle the collisions of bullets and aliens
	//TODO - Maybe use a linked list instead of vector for aliens?
	HandleCollisions();
}

void Game::Render()
{
	m_window.BeginDraw();

	m_player.Render(*(m_window.GetRenderWindow()));
	
	for (std::vector<Bullet*>::const_iterator iter = m_bulletList.begin(); iter != m_bulletList.end(); iter++)
	{
		(*iter)->Render(*(m_window.GetRenderWindow()));
	}
	for (std::vector<Alien*>::const_iterator iter = m_alienList.begin(); iter != m_alienList.end(); iter++)
	{
		(*iter)->Render(*(m_window.GetRenderWindow()));
	}

	m_window.EndDraw();
}

bool Game::HasCollided(Bullet* const bullet, Alien* const alien)
{
	if (bullet->GetPosition().y <= alien->GetPosition().y + alien->GetSize().y &&
		bullet->GetPosition().y >= alien->GetPosition().y &&
		bullet->GetPosition().x >= alien->GetPosition().x &&
		bullet->GetPosition().x <= alien->GetPosition().x + alien->GetSize().x)
	{
		return true;
	}

	return false;
}

void Game::AlienCleanup(std::vector<Alien*>::const_iterator& alienIter)
{
	if (alienIter == m_alienList.end() - 1)
	{
		m_alienList.erase(alienIter);
		if (m_alienList.size() != 0)
		{
			alienIter = m_alienList.begin();
		}
		else
		{
			alienIter = m_alienList.end();
		}
	}
	else
	{
		alienIter = m_alienList.erase(alienIter);
	}
}

bool Game::BulletListEmpty(std::vector<Bullet*>::const_iterator& bulletIter)
{
	if (bulletIter == m_bulletList.end() - 1)
	{
		m_bulletList.erase(bulletIter);
		return true;
	}
	else
	{
		bulletIter = m_bulletList.erase(bulletIter);
		return false;
	}
}

void Game::MoveAliens()
{
	for (int count = 0; count < m_alienList.size(); count++)
	{
		if (m_alienList[count]->GetPosition().x + m_alienList[count]->GetSize().x >= 800 &&
			m_alienList[count]->GetMoveDir() > 0)
		{
			for (int count = 0; count < m_alienList.size(); count++)
			{
				m_alienList[count]->ShiftDown();
				m_alienList[count]->InvertDir();
			}
		}
		else if (m_alienList[count]->GetPosition().x <= 0 &&
			m_alienList[count]->GetMoveDir() < 0)
		{
			for (int count = 0; count < m_alienList.size(); count++)
			{
				m_alienList[count]->ShiftDown();
				m_alienList[count]->InvertDir();
			}
		}
		else
		{
			m_alienList[count]->Move();
		}
	}
}

void Game::HandleCollisions()
{
	for (std::vector<Bullet*>::iterator bulletIter = m_bulletList.begin(); bulletIter != m_bulletList.end(); bulletIter++)
	{
		for (std::vector<Alien*>::iterator alienIter = m_alienList.begin(); alienIter != m_alienList.end();)
		{
			if (HasCollided(*bulletIter, *alienIter))
			{
				AlienCleanup(alienIter);
				if (BulletListEmpty(bulletIter))
				{
					return;
				}
			}
			else
			{
				alienIter++;
			}
		}
	}
}