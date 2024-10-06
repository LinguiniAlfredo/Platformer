#include "vec2.h"

Vec2::Vec2()
{
	x = 0;
	y = 0;
}

Vec2::Vec2(int x, int y)
{
	this->x = x * 8;
	this->y = y * 8;
}

Vec2f::Vec2f()
{
	x = 0;
	y = 0;
}

Vec2f::Vec2f(float x, float y)
{
	this->x = x;
	this->y = y;
}