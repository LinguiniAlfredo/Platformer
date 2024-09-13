#pragma once
#include <SDL.h>
class Collider :
	public SDL_Rect
{
public:
	bool isColliding(SDL_Rect* a, SDL_Rect* b);
private:
};

