#include "Collision.h"

Collision::Collision()
{
	x = 0;
	y = 0;
	width = 0;
	height = 0;
	colliding = false;
}

Collision::Collision(axes position, float w, float h)
{
	x = position.x;
	y = position.y;
	width = w;
	height = h;
	colliding = false;
}

Collision::~Collision()
{

}

bool Collision::isColliding()
{
	return colliding;
}

//void Collision::checkCollision(GameObject& obj)
//{
//
//}

void Collision::setPosition(axes position)
{
	x = position.x;
	y = position.y;
}