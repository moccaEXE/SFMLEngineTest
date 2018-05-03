#pragma once
#include "../../Asteroids/Engine/Game.h"
#include "../../Asteroids/Engine/Configuration.h"
//#include "../Header/Configuration.h"

int main()
{
	Configuration::initialize();
	Game game;
	game.run(30);

	return 0;
}