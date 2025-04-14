#pragma once
#include "Entity.h"
#include "Utils/Utils.h"

class Lift :
	public Entity
{
public:
	using Entity::Entity;

	void update(float deltaTime) override;

private:
	Path path;
	const int speed = 1;

	void move(float deltaTime);
};

