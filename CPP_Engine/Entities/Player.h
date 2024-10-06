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
	Vec2f actualPosition = { static_cast<float>(position.x), static_cast<float>(position.y) };

	const float runAccel = 0.0625; // 1/16th of a pixel accel
	int maxSpeed = 1;
	int groundSpeed = 63;
	int jumpForce	 = 250;

	int currentState = AIRBORNE;
	int power        = NONE;
	bool running	 = false;

	void checkCollisions(float deltaTime) override;

	void checkForFloor();
	void resolveCollision(Entity* ent);
	void move(float deltaTime);

};

