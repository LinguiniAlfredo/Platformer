#pragma once
class Vec2
{
public:
	Vec2();
	Vec2(int x, int y);

    bool operator!=(const Vec2& rhs);

	int x;
	int y;
};

class Vec2f
{
public:
	Vec2f();
	Vec2f(float x, float y);

	float x;
	float y;
};


