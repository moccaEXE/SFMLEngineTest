#pragma once
#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>
#include <Windows.h>
#include "Player.h"


class Game
{
protected:
	//common game properties
	LARGE_INTEGER timeStart;
	LARGE_INTEGER timeEnd;
	LARGE_INTEGER timeFreq;
	float frameTime;
	DWORD sleepTime;
	bool paused;
	bool initialized;

public:
	//constructor
	Game(const Game&) = delete;
	Game& operator =(const Game&) = delete;
	Game();
	void run(int minimum_fps);

private:
	void processEvents();
	void update(sf::Time elapsedTime);
	void render();
	void printFPS(int fps);

	sf::RenderWindow _window;
	Player _player;

};