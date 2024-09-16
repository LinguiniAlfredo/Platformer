#pragma once
#include <SDL.h>
#include "Entity.h"
#include "Utils/Vec2.h"
#include <string>
class Texture;

class Box :
	public Entity
{
public:
	Box(SDL_Renderer* renderer);
	Box(SDL_Renderer* renderer, std::string textureFile, Vec2 currentPosition);
	~Box();

	void draw();
	void update(float deltaTime);

	void setScene(Scene* scene);

	bool isColliding();
	bool hasCollider();
	SDL_Rect* getCollider();

	Vec2 getPosition();

private:
	Scene* scene;

	Texture* texture;
	Vec2 currentPosition;
	const std::string textureFile = "resources/textures/platform.png";

	SDL_Rect* collider;
	bool colliding = false;

	void checkCollisions(float deltaTime);
};

