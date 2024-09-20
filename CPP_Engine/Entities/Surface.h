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
	Surface(Scene* scene);
	Surface(Scene* scene, std::string textureFile, Vec2 currentPosition);
	Surface(Scene* scene, std::string textureFile, Vec2 currentPosition, bool solid);
	~Surface();

	void draw();
	void update(float deltaTime);

	void setScene(Scene* scene);

	bool isColliding();
	bool hasCollider();
	SDL_Rect* getCollider();
	bool isSolid();

	Vec2 getPosition();

private:
	Scene* scene;

	Texture* texture;
	Vec2 currentPosition;
	const std::string textureFile = "resources/textures/platform.png";

	SDL_Rect* collider;
	bool colliding = false;
	bool solid = true;

	void checkCollisions(float deltaTime);
};

