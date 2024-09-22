#pragma once
#include "Surface.h"

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
	const int speed = 1;
	const int range = 10;

	Vec2 currentVelocity = { 0, 1 };
	int frameCount = 0;

	void checkCollisions(float deltaTime);
	void move(float deltaTime);
};

