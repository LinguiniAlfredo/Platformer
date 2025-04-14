#include <SDL.h>
#include "Pallete.h"
#include "Components/Texture.h"


Pallete::Pallete(SDL_Renderer* renderer)
{
	this->renderer = renderer;
	this->box = new SDL_Rect{ xPos, yPos, width, height };
    this->texture = new Texture(renderer,"resources/textures/pallete.png");
}

Pallete::~Pallete()
{
    delete texture;
    texture = nullptr;
	delete box;
	box = nullptr;
}

void Pallete::update()
{
	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
	SDL_RenderFillRect(renderer, box);

    SDL_Rect* outline = new SDL_Rect{xPos-1, yPos-1, width+2, height+2};
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xD7, 0x00, 0xFF);
    SDL_RenderDrawRect(renderer, outline);
    texture->render(xPos, yPos);

    delete outline;
    outline = nullptr;
}

void Pallete::handleEvent(SDL_Event& e)
{

}


