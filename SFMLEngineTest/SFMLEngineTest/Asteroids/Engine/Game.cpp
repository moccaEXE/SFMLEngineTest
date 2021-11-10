#include "Game.h"

#include "Configuration.h"
#include "Random.h"
#include "Meteor.h"
#include "Saucer.h"
#include "Player.h"

Game::Game(int x, int y) : _window(sf::VideoMode(x,y), "Meh asteroids"), _world(x,y)
{
	//_player.setFillColor(sf::Color::Blue);)
	_txt.setFont(Configuration::fonts.get(Configuration::Fonts::Gui));
	_txt.setCharacterSize(70);
	_txt.setString("Press any Key to start");
	sf::FloatRect size = _txt.getGlobalBounds();
	_txt.setOrigin(size.width / 2, size.height / 2);
	_txt.setPosition(x / 2, y / 2);
	//_player.setPosition(100.f, 100.f);
};

void Game::run(int minimum_fps)
{
	sf::Clock clock;
	sf::Time deltaTime;
	sf::Time timePerFrame = sf::seconds(1.f / minimum_fps);

int fps = 0;

while (_window.isOpen())
{
	processEvents();

	deltaTime = clock.restart();

	while (deltaTime > timePerFrame)
	{
		deltaTime -= timePerFrame;
		update(timePerFrame);
		fps++;
	}

	int fps = (int)(1.f / deltaTime.asSeconds());

	printFPS(fps);
	update(deltaTime);
	render();
}
};

void Game::initLevel()
{
	int nb_meteors;
	switch (Configuration::level)
	{
	case 1: nb_meteors = 4; break;
	case 2: nb_meteors = 5; break;
	case 3: nb_meteors = 7; break;
	case 4: nb_meteors = 9; break;
	default: nb_meteors = 11; break;
	}

	for (int i = 0; i < nb_meteors; i++)
	{
		Meteor* meteor = new BigMeteor(_world);
		while (_world.isCollide(*meteor))
		{
			meteor->setPosition((float)random(0.f, (float)_world.getX()), (float)random(0.f, (float)_world.getY()));
		}
		_world.add(meteor);
	}
}

void Game::printFPS(int fps)
{
	COORD c;
	c.X = 0; c.Y = 0;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
	printf("%d", fps);
}

void Game::processEvents()
{
	sf::Event event;
	while (_window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			_window.close();
		else if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				_window.close();
			}
		}

		if (Configuration::isGameOver())
		{
			if (event.type == sf::Event::KeyPressed)
				reset();
		}
		else
		{
			if (Configuration::player != nullptr)
				Configuration::player->processEvent(event);
		}
	}

	if (!Configuration::isGameOver() && Configuration::player != nullptr)
		Configuration::player->processEvents();
}


void Game::update(sf::Time deltaTime)
{
	//	_player.update(deltaTime);
	if (!Configuration::isGameOver())
	{
		_world.update(deltaTime);
		if (Configuration::player == nullptr)
		{
			Configuration::player = new Player(_world);
			Configuration::player->setPosition(_world.getX() / 2, _world.getY() / 2);
			_world.add(Configuration::player);
		}
		_nextSaucer -= deltaTime;

		if(_nextSaucer < sf::Time::Zero)
		{
			Saucer::newSaucer(_world);
			_nextSaucer = sf::seconds(random(10.f, 15.f - Configuration::level * 2));
		}

		if (_world.size() <= 1)
		{
			++Configuration::level;
			initLevel();
		}
	}
}

void Game::render()
{
	_window.clear();

	if (Configuration::isGameOver())
	{
		_window.draw(_txt);
	}
	else
	{
		_window.draw(_world);
		Configuration::draw(_window);
	}
	_window.display();
}

void Game::reset()
{
	_nextSaucer = sf::seconds(random(5.f, 6.f - Configuration::level * 2));
	_world.clear();
	Configuration::player = nullptr;
	Configuration::reset();
	initLevel();
}