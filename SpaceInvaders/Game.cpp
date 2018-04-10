#include "Game.h"

Game::Game():
	m_window(sf::Vector2u(SCREEN_WIDTH, SCREEN_HEIGHT), "Window"),
	m_player(sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 50), 5)
{
	NewGame();
}

Game::~Game()
{
}

void Game::NewGame(std::string text)
{
	std::cout << text << std::endl;

	//Removes all aliens before starting new game
	m_alienList.clear();

	int sprite = 0;
	for (int j = 1; j < row; j++)
	{
		for (int i = 1; i < col; i++)
		{
			Alien* alien = new Alien(sf::Vector2f(i * 70, j * 52), sf::Vector2f(40, 40), sprite);
			m_alienList.push_back(alien);
		}
		sprite++;
		if (sprite > 2)
		{
			sprite = 0;
		}
	}
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
			Bullet* bullet = new Bullet(sf::Vector2f(6, 17), sf::Vector2f(m_player.GetPosition().x - 50, m_player.GetPosition().y));
			m_bulletList.push_back(bullet);
			m_sound.Play("fire.wav");
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
			NewGame("YOU WIN");
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
	for (unsigned int count = 0; count < m_alienList.size(); count++)
	{
		if (m_alienList[count]->GetPosition().x + m_alienList[count]->GetSize().x >= SCREEN_WIDTH &&
			m_alienList[count]->GetMoveDir() > 0)
		{
			for (unsigned int count = 0; count < m_alienList.size(); count++)
			{
				m_alienList[count]->ShiftDown();
				m_alienList[count]->InvertDir();
			}
		}
		else if (m_alienList[count]->GetPosition().x <= 0 &&
			m_alienList[count]->GetMoveDir() < 0)
		{
			for (unsigned int count = 0; count < m_alienList.size(); count++)
			{
				m_alienList[count]->ShiftDown();
				m_alienList[count]->InvertDir();
			}
		}
		else if (m_alienList[count]->GetPosition().y + m_alienList[count]->GetSize().y > m_player.GetPosition().y)
		{
			NewGame("YOU LOSE");
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