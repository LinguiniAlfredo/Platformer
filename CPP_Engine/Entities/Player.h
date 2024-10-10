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
	void incrementCoinCount();

private:
	Vec2f actualPosition = { static_cast<float>(position.x), static_cast<float>(position.y) };

	const float runAccel = 0.03125; // 1/32 of a pixel
	float maxSpeed = 1.0;
	int groundSpeed = 63;
	int jumpForce	 = 250;

	int currentState = AIRBORNE;
	int power        = NONE;
	bool running	 = false;

	int coinCount = 0;

	void checkCollisions(float deltaTime) override;

	void checkForFloor();
	void resolveCollision(Entity* ent);
	void move(float deltaTime);
	void moveCamera();
};

