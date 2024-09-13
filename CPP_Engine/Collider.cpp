#include "Collider.h"

bool Collider::isColliding(SDL_Rect* a, SDL_Rect* b)
{	
	return SDL_HasIntersection(a, b);
}