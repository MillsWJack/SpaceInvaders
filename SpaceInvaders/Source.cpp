#include "Game.h"

int main()
{
	Game game;

	while (!game.GetWindow()->isDone())
	{
		game.HandleInput();
		game.Update();
		game.Render();
	}

	return 0;
}