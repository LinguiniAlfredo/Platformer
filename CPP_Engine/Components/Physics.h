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
	const float gravity = 9.2f;
	const float mass = 0;
};

