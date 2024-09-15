#pragma once
#include "Entity.h"
#include "vec2.h"
#include "Scene.h"
class Texture;
class Physics;

enum state {
	GROUNDED,
	AIRBORNE
};

class Player : 
	public Entity
{
public:
	Player(SDL_Renderer* renderer);
	~Player();

	void draw();
	void update(float deltaTime);
	void handleEvent(SDL_Event& e);

	void setScene(Scene* scene);

	bool isColliding();
	bool hasCollider();
	SDL_Rect* getCollider();

	vec2 getPosition();

private:
	Scene* scene;

	const std::string textureFile = "resources/textures/bird.png";
	static const int speed = 300;

	int currentState = AIRBORNE;
	bool colliding = false;

	vec2 currentVelocity;
	vec2 currentPosition;

	Texture* texture;
	SDL_Rect* collider;
	Physics* physics;

	void checkCollisions(float deltaTime);
	void setState();
	void move(float deltaTime);
};

