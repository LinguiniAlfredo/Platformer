#pragma once
#include <SDL.h>
#include "Entity.h"
#include "Utils/Vec2.h"
#include <string>
class Texture;

enum boxState {
	FULL,
	EMPTY
};

class Box :
	public Entity
{
public:
	Box(Scene* scene);
	Box(Scene* scene, std::string textureFile, Vec2 currentPosition);
	~Box();

	void draw();
	void update(float deltaTime);

	void setScene(Scene* scene);
	void setTexture(std::string path);

	bool isColliding();
	bool hasCollider();
	SDL_Rect* getCollider();

	Vec2 getPosition();

private:
	Scene* scene;
	Texture* texture;
	Vec2 currentPosition;
	SDL_Rect* collider;
	const std::string textureFile = "resources/textures/platform.png";
	bool colliding = false;
	int currentState = FULL;

	void checkCollisions(float deltaTime);
	void openBox();
};

