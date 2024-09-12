#pragma once

class Collision
{
public:
	Collision();
	Collision(axes position, float width, float height);
	~Collision();

	bool isColliding();
	//void checkCollision(GameObject& obj);

	void setPosition(axes position);

private:
	float x;
	float y;
	float width;
	float height;

	bool colliding;
};

