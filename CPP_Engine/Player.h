#pragma once
#include "GameObject.h"
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
	SDL_Rect* collision;
	Physics* physics;

};

