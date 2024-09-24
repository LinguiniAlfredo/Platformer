#pragma once
#include "Entity.h"
#include "Utils/Vec2.h"
#include "Scene.h"
#include "Utils/Timer.h"

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
	Player(Scene* scene);
	Player(Scene* scene, Vec2 pos);
	~Player();

	void draw();
	void update(float deltaTime);
	void handleEvent(SDL_Event& e);

	void setScene(Scene* scene);
	void setPowerLevel(int power);

	Vec2 getPosition();
	Collision* getCollider();

	bool isColliding();
	bool isSolid();

	bool hasCollider();
	bool hasPhysics();

private:
	Scene* scene;
	Texture* texture;
	Collision* collider;
	Physics* physics;
	Vec2 currentVelocity;
	Vec2 currentPosition;

	std::string name = "player";
	static const int groundSpeed = 63;
	int jumpForce = 250;

	const std::string textureFile = "resources/textures/guy.png";
	int currentState = AIRBORNE;
	bool colliding = false;
	bool solid = true;
	int power = NONE;

	void checkForFloor();
	void checkCollisions(float deltaTime);
	void resolveCollision(Entity* ent);
	void move(float deltaTime);
};

