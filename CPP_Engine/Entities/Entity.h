#pragma once
#include <SDL.h>
#include <string>
#include "Utils/Vec2.h"
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
	virtual void setTexture(std::string path) {}

	virtual bool isColliding() { return false; }
	virtual bool hasCollider() { return false; }
	virtual SDL_Rect* getCollider() { return nullptr; }
	virtual bool isSolid() { return false; }
	virtual void setSolid(bool solid) {}

	virtual Vec2 getPosition() { return { 0, 0 }; }

	virtual bool hasPhysics() { return false; }

private:
};