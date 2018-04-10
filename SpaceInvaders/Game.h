#pragma once
#include <SFML\Graphics.hpp>

#include "window.h"
#include "Player.h"
#include "Bullet.h"
#include "Alien.h"
#include "Sound.h"

#include <vector>
#include <iostream>
#include <string>

class Game
{
public:
	Game();
	~Game();

	void NewGame(std::string text = "");
	void HandleInput();
	void Update();
	void Render();

	bool HasCollided(Bullet* const bullet, Alien* const alien);
	void AlienCleanup(std::vector<Alien*>::const_iterator& alienIter);
	bool BulletListEmpty(std::vector<Bullet*>::const_iterator& bulletIter);

	void MoveAliens();
	void HandleCollisions();

	inline window* GetWindow() { return &m_window; }

	const int row = 6;
	const int col = 25;
	const int SCREEN_WIDTH = 1920;
	const int SCREEN_HEIGHT = 1080;

private:
	window m_window;
	Player m_player;
	Sound m_sound;

	std::vector<Bullet*> m_bulletList;
	std::vector<Alien*> m_alienList;

	int frame;
};

