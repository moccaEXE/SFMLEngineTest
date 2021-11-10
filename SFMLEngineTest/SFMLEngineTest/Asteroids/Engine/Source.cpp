#include "Game.h"
//#include "../Header/ActionMap.h"
//#include "../Header/Configuration.h"

int main()
{
	Configuration::initialize();
	Game game;
	game.run(30);

	return 0;
}