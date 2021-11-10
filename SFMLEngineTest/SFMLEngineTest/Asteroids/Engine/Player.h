#pragma once
#include "ActionTarget.h"
#include "Entity.h"

class Player : public Entity, public ActionTarget<int>
{
public:
	Player(const Player&) = delete;
	Player& operator=(const Player&) = delete;
	Player(World& world);

	virtual bool isCollide(const Entity& other) const;
	void update(sf::Time deltaTime);
	void processEvents();
	void shoot();
	void goToHyperspace();
	virtual void onDestroy();

private:

	sf::Time timeSinceLastShoot;
	bool _isMoving;
	int _rotation;
};