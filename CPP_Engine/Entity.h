#pragma once
#include <SDL.h>
class Scene;

class Entity
{
public:
	Entity() {};
	virtual ~Entity() {};

	virtual void draw() {};
	virtual void update(float deltaTime) {};
	virtual void handleEvent(SDL_Event& e) {};

	virtual void setScene(Scene* s) {}

	virtual bool isColliding() { return false; }
	virtual bool hasCollider() { return false; }
	virtual SDL_Rect* getCollider() { return nullptr; }

};