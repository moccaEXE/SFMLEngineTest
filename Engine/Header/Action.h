#pragma once
#include <SFML\Graphics.hpp>

class Action
{
public:

	enum Type
	{
		RealTime = 1,
		Pressed = 1 << 1,
		Released = 1 << 2
	};

	Action(sf::Keyboard::Key key, int type=(Type::RealTime|Type::Pressed));
	Action(sf::Mouse::Button button, int type = (Type::RealTime | Type::Pressed));
	Action::Action(const Action& other);

	bool test() const;

	bool operator==(const sf::Event& event) const;
	bool operator==(const Action& other) const;
	Action& operator=(const Action& other);

private:
	template<typename> friend class ActionTarget;
	sf::Event _event;
	int _type;
};

