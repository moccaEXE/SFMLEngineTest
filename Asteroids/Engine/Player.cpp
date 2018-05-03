#include "Player.h"

#include "Configuration.h"
#include "Collision.h"
#include "World.h"
#include "Shoot.h"
#include "Random.h"

Player::Player(World& world) : Entity(Configuration::Textures::PlayerTexture, world)
, ActionTarget(Configuration::playerInputs)
, _isMoving(false)
, _rotation(0)
{
	bind(Configuration::PlayerInputs::Up, [this](const sf::Event&) {
		_isMoving = true;
	});
	bind(Configuration::PlayerInputs::Left, [this](const sf::Event&) {
		_rotation -= 1;
	});
	bind(Configuration::PlayerInputs::Right, [this](const sf::Event&) {
		_rotation += 1;
	});
	bind(Configuration::PlayerInputs::Shoot, [this](const sf::Event&) {
		shoot();
	});
	bind(Configuration::PlayerInputs::Hyperspace, [this](const sf::Event&) {
		goToHyperspace();
	});
}

bool Player::isCollide(const Entity& other) const
{
	if (dynamic_cast<const ShootPlayer*>(&other) == nullptr)
	{
		return Collision::circleTest(_sprite, other._sprite);
	}
	return false;
}

void Player::shoot()
{
	if (timeSinceLastShoot > sf::seconds(0.3))
	{
		_world.add(new ShootPlayer(*this));
		timeSinceLastShoot = sf::Time::Zero;
	}
}

void Player::goToHyperspace()
{
	_impulse = sf::Vector2f(0.f, 0.f);
	setPosition((float)random(0,_world.getX()), (float)random(0,_world.getY()));
	
	_world.add(Configuration::Sounds::Jump);
}

void Player::update(sf::Time deltaTime)
{
	float seconds = deltaTime.asSeconds();
	timeSinceLastShoot += deltaTime;
	if (_rotation != 0)
	{
		float angle = _rotation * 250 * seconds;
		_sprite.rotate(angle); 
	}
	if (_isMoving)
	{
		float angle = float(_sprite.getRotation() / 180 * M_PI - M_PI/2);
		_impulse += sf::Vector2f(std::cos(angle), std::sin(angle)) * 300.f * seconds; 
	}

	_sprite.move(seconds*_impulse);
}


void Player::processEvents()
{
	_isMoving = false;
	_rotation = 0;
	ActionTarget::processEvents();
}

void Player::onDestroy()
{
	Configuration::player = nullptr;
	Entity::onDestroy();
	Configuration::lives--;
	_world.add(Configuration::Sounds::Boom);
}