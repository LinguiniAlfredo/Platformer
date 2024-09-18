#pragma once
#include <SDL.h>
#include "Entity.h"
#include "Utils/Vec2.h"
#include <string>
class Texture;

class Pickup :
	public Entity
{
public:
	Pickup(Scene* scene);
	Pickup(Scene* scene, std::string itemType, Vec2 currentPosition);
	~Pickup();

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
	Pickup* item;

	void checkCollisions(float deltaTime);
	void openBox();
};

