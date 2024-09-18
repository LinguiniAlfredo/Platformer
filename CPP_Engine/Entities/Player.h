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

	bool isColliding();
	bool hasCollider();
	SDL_Rect* getCollider();
	bool isSolid();

	Vec2 getPosition();

	bool hasPhysics();

	void setPowerUp(int power);

private:
	Scene* scene;

	static const int groundSpeed = 63;
	int jumpForce = 200;

	const std::string textureFile = "resources/textures/guy.png";
	int currentState = AIRBORNE;
	bool colliding = false;
	Vec2 currentVelocity;
	Vec2 currentPosition;
	Texture* texture;
	SDL_Rect* collider;
	Physics* physics;
	Timer jumpTimer;
	bool solid = true;
	int power = NONE;

	void checkForFloor();
	void checkCollisions(float deltaTime);
	void resolveCollision(Entity* ent);
	void move(float deltaTime);
};

