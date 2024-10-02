#pragma once
#include "Entity.h"

enum playerState {
	GROUNDED,
	AIRBORNE
};

enum power {
	NONE,
	FLOWER
};

class Player : 
	public Entity
{
public:
	using Entity::Entity;

	void update(float deltaTime) override;
	void handleEvent(SDL_Event& e) override;

	void setPowerLevel(int power);

private:
	static const int maxRunSpeed = 5;
	static const int minRunSpeed = 1;
	static const int runAccel    = 1;
	static const int groundSpeed = 63;
	static const int jumpForce	 = 250;

	int currentState = AIRBORNE;
	int power        = NONE;
	bool running	 = false;

	void checkCollisions(float deltaTime) override;

	void checkForFloor();
	void resolveCollision(Entity* ent);
	void move(float deltaTime);
};

