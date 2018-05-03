#pragma once
#include <SFML\Graphics.hpp>
#include <utility>
#include "Configuration.h"

class World; 
class Entity : public sf::Drawable
{
public:
	// Constructors
	Entity(const Entity&)= delete;
	Entity& operator= (const Entity&) = delete;
	Entity(Configuration::Textures tex_id, World& world);

	// Helpers
	virtual bool isAlive() const;
	template<typename ... Args>
	void setPosition(Args&& ... args);

//	void setPosition(const sf::Vector2f& pos);
	virtual bool isCollide(const Entity& other) const = 0;

	const sf::Vector2f& getPosition()const { return _sprite.getPosition(); }

	// Updates
	virtual void update(sf::Time deltaTime) = 0;
	virtual void onDestroy();

	sf::Sprite _sprite;

protected:

	friend class Meteor;
	friend class Player;
	friend class Saucer;
	friend class ShootPlayer;
	friend class ShootSaucer;

	sf::Vector2f _impulse;
	World& _world;
	bool _alive;

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

//void Entity::setPosition(const sf::Vector2f& pos)
//{
//	_sprite.setPosition(pos);
//}


template<typename ... Args>
void Entity::setPosition(Args&& ... args)
{
	_sprite.setPosition(std::forward<Args>(args) ... );
}