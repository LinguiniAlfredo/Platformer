#include "Collision.h"
#include "Texture.h"

Collision::Collision(SDL_Renderer* renderer, int x, int y, int w, int h)
{
	this->renderer = renderer;
	this->box = new SDL_Rect{ x, y, w, h};
}

Collision::~Collision()
{
	delete box;
	box = nullptr;
}

SDL_Rect* Collision::getBox()
{
	return box;
}