#pragma once
class Physics
{
public:
	Physics();
	~Physics();

	float getGravity();
	float getMass();

	void applyGravity();

private:
	const float gravity = 5.0f;
	const float mass = 0;
};

