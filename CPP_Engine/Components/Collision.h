#pragma once
#include "SDL.h"
#include "Texture.h"
#include "../Utils/Timer.h"

class Collision
{
public:
	Collision(SDL_Renderer* renderer, int x, int y, int w, int h );
	~Collision();

	void render(bool colliding);

	SDL_Rect* getBox();

private:
	SDL_Renderer* renderer;
	SDL_Rect* box;
	Texture* collidingTexture;
	Texture* notCollidingTexture;
};