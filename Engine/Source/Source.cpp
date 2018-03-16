#include "../Header/Game.h"

int main()
{
	Player::setDefaultsInputs();
	Game game;
	game.run(30);

	return 0;
}