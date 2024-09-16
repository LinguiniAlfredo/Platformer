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
	const float gravity = 9.8f;
	const float mass = 0;
};

