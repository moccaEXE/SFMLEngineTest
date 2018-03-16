#pragma once
#include <SFML\Graphics.hpp>
#include "ActionTarget.h"

#define _USE_MATH_DEFINES
#include <math.h>

class Player : public sf::Drawable, public ActionTarget<int>
{
public:
	Player(const Player&) = delete;
	Player& operator=(const Player&) = delete;
	Player();
	template<typename ... Args>
	void setPosition(Args&& ... args);
	void processEvents();
	void update(sf::Time deltaTime);
	enum PlayerInputs { Up, Left, Right };
	static void setDefaultsInputs();
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates
		states) const override;
	sf::RectangleShape _shape;
	sf::Vector2f _velocity;
	bool _isMoving;
	int _rotation;
	static ActionMap<int> _playerInputs;
};


template<typename ... Args>
void Player::setPosition(Args&& ... args)
{
	_shape.setPosition(std::forward<Args>(args)...);
}
