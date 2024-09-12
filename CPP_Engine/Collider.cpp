#include "Collider.h"

bool Collider::getCollisions(SDL_Rect* a, SDL_Rect* b)
{	
	return SDL_HasIntersection(a, b);
}