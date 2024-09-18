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
	Pickup(Scene* scene, std::string itemType);
	Pickup(Scene* scene, std::string itemType, Vec2 pos);
	~Pickup();

	void draw();
	void update(float deltaTime);

	void setScene(Scene* scene);

	bool isColliding();
	bool hasCollider();
	SDL_Rect* getCollider();
	bool isSolid();

	Vec2 getPosition();
	void setPosition(int x, int y);

private:
	Scene* scene;
	Texture* texture;
	Vec2 currentPosition;
	SDL_Rect* collider;
	bool colliding = false;
	bool solid = false;

	void checkCollisions(float deltaTime);
};

