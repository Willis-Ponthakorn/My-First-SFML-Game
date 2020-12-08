#include "stdafx.h"
#include "Game.h"

int main()
{
	Game game;

	while (game.getWindowIsOpen())
	{
		game.run();
	}
	return 0;
}