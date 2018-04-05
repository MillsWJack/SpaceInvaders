#pragma once
#include <SFML\Graphics.hpp>

#include "window.h"
#include "Player.h"
#include "Bullet.h"
#include "Alien.h"

#include <vector>
#include <iostream>

class Game
{
public:
	Game();
	~Game();

	void HandleInput();
	void Update();
	void Render();

	bool HasCollided(Bullet* const bullet, Alien* const alien);
	void AlienCleanup(std::vector<Alien*>::const_iterator& alienIter);
	bool BulletListEmpty(std::vector<Bullet*>::const_iterator& bulletIter);

	void MoveAliens();
	void HandleCollisions();

	inline window* GetWindow() { return &m_window; }

	const int row = 4;
	const int col = 13;

private:
	window m_window;

	Player m_player;

	std::vector<Bullet*> m_bulletList;
	std::vector<Alien*> m_alienList;
};

