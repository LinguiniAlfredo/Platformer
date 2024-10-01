#pragma once
#include "Surface.h"
#include "Utils/Utils.h"

enum pattern {
	UPDOWN
};

class Lift :
	public Surface
{
public:
	using Surface::Surface;

	void update(float deltaTime);

	Vec2 getVelocity();
	void setVelocity(Vec2 velocity);

private:
	Path path;
	Vec2 currentVelocity;

	const int speed = 1;

	void checkCollisions(float deltaTime);
	void move(float deltaTime);
};

