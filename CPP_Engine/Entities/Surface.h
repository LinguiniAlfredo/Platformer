#pragma once
#include <SDL.h>
#include "Entity.h"
#include "Utils/Vec2.h"
#include <string>
class Texture;

class Surface :
	public Entity
{
public:
	Surface(SDL_Renderer* renderer);
	Surface(SDL_Renderer* renderer, std::string textureFile, Vec2 currentPosition);
	~Surface();

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

