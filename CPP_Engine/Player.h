#pragma once
#include "GameObject.h"

class Player : 
	public GameObject
{
public:
	Player(string name, double width, double height, coordinates position, SDL_Texture* texture);
	~Player();

	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();

private:
};

