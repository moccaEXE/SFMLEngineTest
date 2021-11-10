#include "Saucer.h"

#include "Random.h"
#include "World.h"
#include "Meteor.h"
#include "Shoot.h"
#include "Collision.h"
#include "Player.h"

#include <cfloat>
#include <Windows.h>

bool Saucer::isCollide(const Entity& other) const
{
	if (dynamic_cast<const ShootSaucer*>(&other) == nullptr)
	{
		return Collision::circleTest(_sprite, other._sprite);
	}
	return false;
}

Saucer::Saucer(Configuration::Textures textures, World& world) : Enemy(textures, world)
{

}

void Saucer::update(sf::Time deltaTime)
{
	float seconds = deltaTime.asSeconds();

	Entity* nearEntity = nullptr;
	float near_distance = 300;

	for (Entity* entity_ptr : _world.getEntities())
	{
		if (entity_ptr != this && (dynamic_cast<const Meteor*>(entity_ptr) || dynamic_cast<const ShootPlayer*>(entity_ptr)))
		{
			float x = getPosition().x - entity_ptr->getPosition().x;
			float y = getPosition().y - entity_ptr->getPosition().y;

			float dist = std::sqrt(x*x + y*y);

			if (dist < near_distance)
			{
				near_distance = dist;
				nearEntity = entity_ptr;
			}
		}
	}
	if (nearEntity != nullptr)
	{
		sf::Vector2f pos = nearEntity->getPosition() - getPosition();
		float angle_rad = std::atan2(pos.y, pos.x);
		_impulse -= sf::Vector2f(std::cos(angle_rad), std::sin(angle_rad)) *300.f * seconds;
	}
	else
	{
		sf::Vector2f pos = Configuration::player->getPosition() - getPosition();
		float angle_rad = std::atan2(pos.y, pos.x);
		_impulse += sf::Vector2f(std::cos(angle_rad), std::sin(angle_rad)) * 100.f * seconds;
	}
	//_impulse = sf::Vector2f(1.f,1.f);
	COORD c;
	c.X = 0; c.Y = 1;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
	printf("X: %d  Y: %d  impulse x: %d  impuse y: %d", getPosition().x, getPosition().y, _impulse.x, _impulse.y);
	_sprite.move(seconds * _impulse);
}

void Saucer::onDestroy()
{
	Enemy::onDestroy();
	_world.add(Configuration::Sounds::Boom);
}

void Saucer::newSaucer(World& world)
{
	Saucer* res = nullptr;
	if (random(0.f, 1.f) > Configuration::getScore() / 40000.f)
	{
		res = new BigSaucer(world);
	}
	else
	{
		res = new SmallSaucer(world);
	}

	res->setPosition((float)random(0.f, 1.f)*world.getX(), (float)random(0.f, (float)world.getY()));
	world.add(res);
}

BigSaucer::BigSaucer(World& world) : Saucer(Configuration::Textures::BigSaucer, world)
{
	_world.add(Configuration::Sounds::SaucerSpawn1);
	_impulse *= 300.f;
}

int BigSaucer::getPoints()const
{
	return 50;
}

SmallSaucer::SmallSaucer(World& world) : Saucer(Configuration::Textures::SmallSaucer, world)
{
	_timeSinceLastShoot = sf::Time::Zero;
	_world.add(Configuration::Sounds::SaucerSpawn2);
	_impulse *= 400.f;
}

int SmallSaucer::getPoints()const
{
	return 200;
}

void SmallSaucer::update(sf::Time deltaTime)
{
	Saucer::update(deltaTime);
	//shoot on the Configuration::player
	_timeSinceLastShoot += deltaTime;
	if (_timeSinceLastShoot > sf::seconds(1.5))
	{
		if (Configuration::player != nullptr)
			_world.add(new ShootSaucer(*this));
		_timeSinceLastShoot = sf::Time::Zero;
	}
}
