#pragma once
#include <SDL.h>
#include "Entity.h"
#include "vec2.h"
#include <string>
class Texture;

class Wall :
	public Entity
{
public:
	Wall(SDL_Renderer* renderer);
	~Wall();

	void draw();
	void update(float deltaTime);

	void setScene(Scene* scene);

	bool isColliding();
	bool hasCollider();
	SDL_Rect* getCollider();

private:
	Scene* scene;

	Texture* texture;
	vec2 currentPosition;
	const std::string textureFile = "resources/textures/wall.png";

	SDL_Rect* collider;
	bool colliding = false;

	void checkCollisions(float deltaTime);
};

