#include "../Header/Player.h"

Player::Player() : ActionTarget(Configuration::playerInputs)
, _isMoving(false)
, _rotation(0)
{
	_sprite.setTexture(Configuration::textures.get(Configuration::Textures::Player));
	_sprite.setOrigin(24, 32);
	bind(Configuration::PlayerInputs::Up, [this](const sf::Event&) {
		_isMoving = true;
	});
	bind(Configuration::PlayerInputs::Left, [this](const sf::Event&) {
		_rotation -= 1;
	});
	bind(Configuration::PlayerInputs::Right, [this](const sf::Event&) {
		_rotation += 1;
	});
}


void Player::setDefaultsInputs()
{
}


void Player::update(sf::Time deltaTime)
{
	float seconds = deltaTime.asSeconds();
	if (_rotation != 0)
	{
		float angle = _rotation * 180 * seconds;
		_sprite.rotate(angle); 
	}
	if (_isMoving)
	{
		float angle = float(_sprite.getRotation() / 180 * M_PI - M_PI/2);
		_velocity += sf::Vector2f(std::cos(angle), std::sin(angle)) * 60.f * seconds; 
	}

	_sprite.move(seconds*_velocity);
}


void Player::processEvents()
{
	_isMoving = false;
	_rotation = 0;
	ActionTarget::processEvents();
	
	//isMoving = sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
	//rotation = 0;
	//rotation -= sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
	//rotation += sf::Keyboard::isKeyPressed(sf::Keyboard::Right);
	
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states)
const
{
	target.draw(_sprite, states);
}