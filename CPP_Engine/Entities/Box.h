#pragma once
#include <SDL.h>
#include "Entity.h"
#include "Utils/Vec2.h"
#include <string>
class Texture;
class Pickup;
class Collision;

enum boxState {
	FULL,
	EMPTY
};

class Box :
	public Entity
{
public:
	Box(Scene* scene, Pickup* item, Vec2 currentPosition);
	~Box();

	void draw();
	void update(float deltaTime);

	void setScene(Scene* scene);
	void setTexture(std::string path);

	bool isColliding();
	bool hasCollider();
	Collision* getCollider();
	bool isSolid();

	Vec2 getPosition();

private:
	Scene* scene;
	Texture* texture;
	Vec2 currentPosition;
	Collision* collider;
	const std::string textureFile = "resources/textures/box.png";
	bool colliding = false;
	int currentState = FULL;
	Pickup* item;
	bool solid = true;

	void checkCollisions(float deltaTime);
	void openBox();
	void revealItem();
};

