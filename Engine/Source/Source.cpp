#include <SFML\Graphics.hpp>
//#include "ResourceManager.cpp"
//#include "ResourceManager.h"
#include <iostream>
#include "../Header/ResourceHolder.hpp"

// resource ID for sf::Texture
namespace Textures
{
	enum ID
	{
		Landscape, Airplane,
	};
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(640, 480), "Resources!!!");
	window.setFramerateLimit(20);

	// Try to load textures
	ResourceManager<sf::Texture, Textures::ID> textures;

	try
	{
		textures.load(Textures::Landscape, "SFMLEngineTest/Media/Textures/Desert.png");
		textures.load(Textures::Airplane, "SFMLEngineTest/Media/Textures/Eagle.png");
	}

	catch (std::runtime_error& e)
	{
		std::cout << "Exception " << e.what() << std::endl;
		return 1;
	}

	// Access resources
	sf::Sprite landscape(textures.get(Textures::Landscape));
	sf::Sprite airplane(textures.get(Textures::Airplane));

	airplane.setPosition(200.f, 200.f);

//	sf::CircleShape shape(100.f);
//	shape.setFillColor(sf::Color::Green);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{	
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(landscape);
		window.draw(airplane);
		window.display();
	}

	return 0;
}