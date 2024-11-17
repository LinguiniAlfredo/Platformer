#include <SDL.h>
#include "Pallete.h"


Pallete::Pallete(SDL_Renderer* renderer)
{
	this->renderer = renderer;
	this->box = new SDL_Rect{ xPos, yPos, width, height };
}

Pallete::~Pallete()
{
	delete box;
	box = nullptr;
}

void Pallete::update()
{
	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xFF, 0xFF);
	SDL_RenderDrawRect(renderer, box);
}

void Pallete::handleEvent(SDL_Event& e)
{

}
