#pragma once
#include "Entity.h"
#include "../Scene.h"
#include "../Utils/Vec2.h"
#include "../Utils/Timer.h"

class Texture;
class Physics;

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

	void update(float deltaTime);
	void handleEvent(SDL_Event& e);

	void setPowerLevel(int power);

private:
	static const int maxRunSpeed = 5;
	static const int minRunSpeed = 1;
	static const int runAccel    = 1;
	int groundSpeed				 = 63;
	int jumpForce				 = 250;

	int currentState = AIRBORNE;
	int power        = NONE;
	bool running	 = false;

	void checkCollisions(float deltaTime) override;

	void checkForFloor();
	void resolveCollision(Entity* ent);
	void move(float deltaTime);
};

