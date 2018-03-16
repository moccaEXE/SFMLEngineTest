#include "../Header/Game.h"

Game::Game() : _window(sf::VideoMode(800,600), "Game Engine Test")
{
	//_player.setFillColor(sf::Color::Blue);
	
	_player.setPosition(100, 100);
};

void Game::run(int minimum_fps)
{
	sf::Clock clock;
	sf::Time elapsedTime = sf::Time::Zero;
	sf::Time timePerFrame = sf::seconds(1.f / minimum_fps);

	while (_window.isOpen())
	{
		processEvents();

		elapsedTime += clock.restart();

		while (elapsedTime > timePerFrame)
		{
			elapsedTime -= timePerFrame;
			update(timePerFrame);
		}
		update(elapsedTime);
		render();
	}
};

void Game::processEvents()
{
	sf::Event event;
	while (_window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed )
			_window.close();
		else if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				_window.close();
			}
		}
	}

	_player.processEvents();
};

void Game::update(sf::Time elapsedTime)
{
	_player.update(elapsedTime);
};

void Game::render()
{
	_window.clear();
	_window.draw(_player);
	_window.display();
};