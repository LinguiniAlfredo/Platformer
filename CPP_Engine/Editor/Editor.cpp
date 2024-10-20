#include <SDL.h>
#include "Editor.h"
#include "Pallete.h"
#include "Mouse.h"

Editor::Editor(SDL_Renderer* renderer) 
{
	this->renderer = renderer;
	this->mouse = new Mouse();
	this->pallete = nullptr;
}

Editor::~Editor() 
{
	delete mouse;
	mouse = nullptr;

	if (pallete != nullptr) {
		delete pallete;
		pallete = nullptr;
	}
}

void Editor::update() 
{
	if (palleteOpen) {
		pallete->update();
	}
	highlightHoveredTiles();
}

void Editor::handleEvents(SDL_Event& e)
{
	if (e.type == SDL_KEYDOWN) {
		switch (e.key.keysym.sym) {
			case SDLK_TAB:
				togglePallete();
				break;
			default:
				break;
		}
	}

	mouse->handleEvent(e);
	if (palleteOpen) {
		pallete->handleEvent(e);
	}
}

void Editor::togglePallete()
{
	palleteOpen = !palleteOpen;
	if (palleteOpen) {
		pallete = new Pallete(renderer);
	}
	else {
		delete pallete;
		pallete = nullptr;
	}
}

SDL_Renderer* Editor::getRenderer()
{
	return renderer;
}

Pallete* Editor::getPallete()
{
	return pallete;
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
	delete box;
	box = nullptr;
}