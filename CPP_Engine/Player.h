#pragma once
#include "Entity.h"
#include "vec2.h"
#include "Scene.h"
class Texture;
class Physics;

enum state {
	GROUNDED,
	JUMPING,
	FALLING
};

class Player : 
	public Entity
{
public:
	Player(SDL_Renderer* renderer);
	Player(SDL_Renderer* renderer, vec2 pos);
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

	static const int groundSpeed = 100;
	static const int airSpeed = 50;
	static const int jumpForce = 300;
	static const int jumpHeight = 100;

	const std::string textureFile = "resources/textures/guy.png";
	int currentState = FALLING;
	bool colliding = false;
	vec2 currentVelocity;
	vec2 currentPosition;
	Texture* texture;
	SDL_Rect* collider;
	Physics* physics;

	void checkCollisions(float deltaTime);
	void move(float deltaTime);
};

