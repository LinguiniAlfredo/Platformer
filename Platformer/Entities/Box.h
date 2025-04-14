#pragma once
#include <string>
#include "Entity.h"
#include "../Utils/Vec2.h"
class Pickup;

enum boxState {
	FULL,
	EMPTY
};

class Box :
	public Entity
{
public:
	Box(Scene* scene, Pickup* item, Vec2 currentPosition);
	~Box();

private:
	Pickup* item;
	const std::string textureFile = "resources/textures/box.png";
	int currentState;

	void checkCollisions(float deltaTime) override;
	void openBox();
	void revealItem();
};

