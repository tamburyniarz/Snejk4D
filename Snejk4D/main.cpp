
#include "game.h"
#include <iostream>

int main()
{
	Game * game = new Game();

	if (game->Initialize() == -1)
		return -1;

	game->Start();

	delete game;
	return 0;
}
