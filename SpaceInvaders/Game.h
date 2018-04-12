#pragma once
#include <SFML\Graphics.hpp>

#include "window.h"
#include "Player.h"
#include "Bullet.h"
#include "Alien.h"
#include "Sound.h"
#include "Score.h"

#include <vector>
#include <iostream>
#include <string>

class Game
{
public:
	Game();
	~Game();

	void NewGame();
	void HandleInput();
	void Update();
	void Render();

	bool HasCollided(Bullet* const bullet, Alien* const alien);
	void AlienCleanup(std::vector<Alien*>::const_iterator& alienIter);
	void BulletCleanup();
	bool BulletListEmpty(std::vector<Bullet*>::const_iterator& bulletIter);

	void MoveAliens();
	void HandleCollisions();

	inline window* GetWindow() { return &m_window; }

	const int row = 6;
	const int col = 12;
	const int SCREEN_WIDTH = 1920;
	const int SCREEN_HEIGHT = 1080;

private:
	window m_window;
	Player m_player;

	Score m_scoreTitle;
	Score m_scoreFigure;
	Score m_gameStatus;

	Sound m_shotSound;
	Sound m_explodeSound;
	Sound m_shiftSound;

	std::vector<Bullet*> m_bulletList;
	std::vector<Alien*> m_alienList;

	int score;
};

