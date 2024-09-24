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
	void setSolid(bool solid);
	void setTexture(std::string texture);
	void setColliding(bool colliding);
	void setPosition(Vec2 position);
	void setColliderPosition(Vec2 position);

	Scene* getScene();
	Collision* getCollider();
	bool isColliding();
	bool hasCollider();
	bool isSolid();

	Vec2 getPosition();

private:
	Scene* scene;

	Texture* texture;
	Vec2 currentPosition;
	std::string textureFile = "resources/textures/platform.png";

	Collision* collider;
	bool colliding = false;
	bool solid = true;

	void checkCollisions();
};

