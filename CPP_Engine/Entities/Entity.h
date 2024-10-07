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
	Entity(Scene* scene, std::string textureFile, Vec2 position, bool solid);
	virtual ~Entity();

	virtual void draw();
	virtual void update(float deltaTime);
	virtual void handleEvent(SDL_Event& e);

	virtual Scene* getScene();
	virtual Texture* getTexture();
	virtual Collision* getCollider();
	virtual Vec2 getPosition();
	virtual Vec2f getVelocity();

	virtual void setScene(Scene* s);
	virtual void setTexture(std::string path);
	virtual void setSolid(bool solid);
	virtual void setPosition(int x, int y);
	virtual void setColliderPosition(int x, int y);
	virtual void setColliding(bool colliding);

	virtual bool isColliding();
	virtual bool isSolid();

	virtual bool hasCollider();
	virtual bool hasPhysics();

	virtual bool inView();

protected:
	Scene* scene;
	Texture* texture;
	Collision* collider;
	Physics* physics;
	Vec2f velocity;
	Vec2 position;

	bool solid = true;
	bool colliding = false;

	virtual void checkCollisions(float deltaTime);
};