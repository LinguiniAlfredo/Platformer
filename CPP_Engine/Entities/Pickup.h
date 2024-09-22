#pragma once
#include <SDL.h>
#include "Entity.h"
#include "Utils/Vec2.h"
#include <string>
#include "Player.h"
class Texture;
class Physics;

class Pickup :
	public Entity
{
public:
	Pickup(Scene* scene, std::string itemType, bool physics);
	Pickup(Scene* scene, std::string itemType, Vec2 pos, bool physics);
	~Pickup();

	void draw();
	void update(float deltaTime);

	void setScene(Scene* scene);

	bool isColliding();
	bool hasCollider();
	Collision* getCollider();
	bool isSolid();

	Vec2 getPosition();
	void setPosition(int x, int y);


private:
	Scene* scene;
	Texture* texture;
	Vec2 currentPosition;
	Vec2 currentVelocity;
	Collision* collider;
	Physics* physics;

	int currentState = AIRBORNE;

	bool colliding = false;
	bool solid = false;
	std::string type;

	void checkCollisions(float deltaTime);
	void resolveCollision(Entity* ent);
	void checkForFloor();
	void move(float deltaTime);
};

