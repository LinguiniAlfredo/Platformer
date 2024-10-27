#pragma once
#include <SDL.h>

class Pallete
{
public:
	Pallete(SDL_Renderer* renderer);
	~Pallete();

	void update();
	void handleEvent(SDL_Event& e);

private:
	SDL_Renderer* renderer;
	SDL_Rect* box;
};