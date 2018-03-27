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

	bool HasCollided(Bullet* bullet, Alien* alien);
	void HandleCollision(Alien* alien);

	window* GetWindow() { return &m_window; }

private:
	window m_window;

	Player m_player;

	std::vector<Bullet*> m_bulletList;
	std::vector<Alien*> m_alienList;
};

