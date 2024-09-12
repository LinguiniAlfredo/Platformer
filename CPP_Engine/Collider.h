#pragma once
#include <SDL.h>
class Collider :
	public SDL_Rect
{
public:
	using SDL_Rect::SDL_Rect;
	bool getCollisions(SDL_Rect* a, SDL_Rect* b);
private:
};

