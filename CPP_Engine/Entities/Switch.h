#pragma once
#include <SDL.h>
#include "Entity.h"
#include "Utils/Vec2.h"
#include <string>
#include <vector>
class Texture;
class Pickup;
class Surface;

class Switch :
	public Entity
{
public:
	Switch(Scene* scene, std::vector<Surface*> switchBlocks, Vec2 currentPosition);
	Switch(Scene* scene, std::vector<Surface*> switchBlocks, std::string color, Vec2 currentPosition);
	Switch(Scene* scene, std::vector<Surface*> switchBlocks, std::string color, Vec2 currentPosition, bool on);
	~Switch();

	void draw();
	void update(float deltaTime);

	void setScene(Scene* scene);
	void setTexture(std::string path);

	bool isColliding();
	bool hasCollider();
	Collision* getCollider();
	bool isSolid();

	Vec2 getPosition();

	void onOff();

private:
	Scene* scene;
	Texture* texture;
	Collision* collider;
	Vec2 currentPosition;

	std::string color = "blue";
	std::string onTexture = "resources/textures/switch_blue.png";
	std::string offTexture = "resources/textures/switch_off.png";

	std::vector<Surface*> switchBlocks;

	bool colliding = false;
	bool on = false;
	bool solid = true;

	void checkCollisions(float deltaTime);
	void openBox();
	void revealItem();
};

