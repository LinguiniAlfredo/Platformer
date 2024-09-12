#pragma once
#include "GameObject.h"
#include "Collision.h"
#include "Physics.h"

class Player : 
	public GameObject
{
public:
	Player();
	~Player();

	void move();
	void jump();

private:
	Collision* collision;
	Physics* physics;

};

