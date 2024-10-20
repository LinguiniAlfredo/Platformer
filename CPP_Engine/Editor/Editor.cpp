#include "Editor.h"
#include <SDL.h>

Editor::Editor(SDL_Renderer* renderer) 
{
	this->renderer = renderer;
	this->mouse = new Mouse();
}

Editor::~Editor() 
{
	delete mouse;
	mouse = nullptr;
}

void Editor::update() 
{
	printf("%d, %d \n", mouse->getPosition().x, mouse->getPosition().y);
	highlightHoveredTiles();
}

void Editor::pollEvents(SDL_Event e)
{
	while (SDL_PollEvent(&e) != 0) {
		mouse->handleEvent(e);
	}
}

Mouse* Editor::getMouse()
{
	return mouse;
}

void Editor::highlightHoveredTiles()
{
	Vec2 tilePos = { mouse->getPosition().x / 192, mouse->getPosition().y / 192 };
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_Rect* box = new SDL_Rect{ tilePos.x, tilePos.y, 8, 8};
	SDL_RenderDrawRect(renderer, box);
}