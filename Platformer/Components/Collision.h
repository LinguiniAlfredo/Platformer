#pragma once
#include "SDL.h"
#include "../Utils/Timer.h"

class Collision
{
public:
	Collision(SDL_Renderer* renderer, int x, int y, int w, int h );
	~Collision();

	SDL_Rect* getBox();

private:
	SDL_Renderer* renderer;
	SDL_Rect* box;
};