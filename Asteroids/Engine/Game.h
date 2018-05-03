#pragma once
#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>
#include <Windows.h>
#include "World.h"


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
	Game(int x = 1600, int y = 900);
	void run(int minimum_fps = 30);
	void initLevel();

private:
	void processEvents();
	void update(sf::Time deltaTime);
	void render();
	void printFPS(int fps);

	void reset();

	sf::RenderWindow _window;
	World _world;
	sf::Time _nextSaucer;
	sf::Text _txt;
};