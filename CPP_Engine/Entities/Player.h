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

	Vec2 getPosition();

	bool hasPhysics();

private:
	Scene* scene;

	static const int groundSpeed = 63;
	static const int jumpForce = 200;

	const std::string textureFile = "resources/textures/guy.png";
	int currentState = AIRBORNE;
	bool colliding = false;
	Vec2 currentVelocity;
	Vec2 currentPosition;
	Texture* texture;
	SDL_Rect* collider;
	Physics* physics;
	Timer jumpTimer;

	void checkForFloor();
	void checkCollisions(float deltaTime);
	void resolveCollision(Entity* ent);
	void move(float deltaTime);
};

