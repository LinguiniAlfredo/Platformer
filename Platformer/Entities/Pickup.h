#pragma once
#include <string>
#include "Entity.h"
#include "Player.h"
#include "../Utils/Vec2.h"

class Pickup :
	public Entity
{
public:
	Pickup(Scene* scene, std::string itemType, bool physics); // used when placing item in box
	Pickup(Scene* scene, std::string itemType, Vec2 pos, bool physics);
	~Pickup();

	void update(float deltaTime) override;

private:
	int currentState = AIRBORNE;

	std::string type;

	void checkCollisions(float deltaTime) override;
	void resolveCollision(Entity* ent);
	void checkForFloor();
	void move(float deltaTime);
};

