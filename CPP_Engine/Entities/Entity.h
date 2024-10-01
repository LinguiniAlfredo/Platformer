#pragma once
#include <SDL.h>
#include <string>
#include "../Utils/Vec2.h"

class Collision;
class Scene;
class Texture;
class Physics;

class Entity
{
public:
	Entity();
	Entity(Scene* scene, std::string textureFile, Vec2 position);
	virtual ~Entity();

	virtual void draw();
	virtual void update(float deltaTime);
	virtual void handleEvent(SDL_Event& e);

	virtual Scene* getScene();
	virtual Texture* getTexture();
	virtual Collision* getCollider();
	virtual Vec2 getPosition();
	virtual Vec2 getVelocity();

	virtual void setScene(Scene* s);
	virtual void setTexture(std::string path);
	virtual void setSolid(bool solid);
	virtual void setPosition(Vec2 position);

	virtual bool isColliding();
	virtual bool isSolid();

	virtual bool hasCollider();
	virtual bool hasPhysics();

protected:
	Scene* scene;
	Texture* texture;
	Collision* collider;
	Physics* physics;
	Vec2 currentVelocity;
	Vec2 currentPosition;

	bool solid = false;
	bool colliding = false;

	virtual void checkCollisions(float deltaTime);
};