#pragma once
#include "Entity.h"
#include "Utils/Utils.h"

enum pattern {
	UPDOWN
};

class Lift :
	public Entity
{
public:
	using Entity::Entity;

	void update(float deltaTime) override;

private:
	Path path;

	const int speed = 1;

	void checkCollisions(float deltaTime) override;
	void move(float deltaTime);
};

