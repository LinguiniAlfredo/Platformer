#pragma once
#include "Entity.h"

class Floor :
	public Entity
{
public:
	Floor();
	~Floor();

	void draw();
	void update();

	void setScene(Scene* scene);

	bool isColliding();
	bool hasCollider();
	SDL_Rect* getCollider();
};

