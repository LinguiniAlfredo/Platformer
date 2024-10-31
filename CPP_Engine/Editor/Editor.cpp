#include <SDL.h>
#include "Editor.h"
#include "Pallete.h"
#include "Mouse.h"
#include "Components/Texture.h"
#include "Utils/Vec2.h"
#include "Scene.h"
#include "Map.h"

Editor::Editor(SDL_Renderer* renderer, Scene* scene)
{
	this->scene = scene;
	this->renderer = renderer;
	this->font = TTF_OpenFont("resources/fonts/nintendo-nes-font.ttf", 28);
	this->mouse = new Mouse();
	this->pallete = nullptr;
	this->mousePosTexture = new Texture(renderer, "0, 0", font, fontColor, 15, 5);
	this->initialCamPosition = { scene->getCamera()->x / 8, scene->getCamera()->y / 8 };
	this->camMoveDir = 0;
}

Editor::~Editor() 
{
	delete mouse;
	mouse = nullptr;

	if (pallete != nullptr) {
		delete pallete;
		pallete = nullptr;
	}
	if (mousePosTexture != nullptr) {
		mousePosTexture->free();
		mousePosTexture = nullptr;
	}
	scene->getCamera()->x = initialCamPosition.x;
	scene->getCamera()->y = initialCamPosition.y;

}

void Editor::update() 
{
	mouse->update();
	if (palleteOpen) {
		pallete->update();
	}

	if (mouse->leftClickDown()) {
		writeTileToMap(mouse->getTilePosition());
	}
	if (mouse->rightClickDown()) {
		
	}


	renderMousePos();
	highlightHoveredTiles();

	moveCamera(camMoveDir);
}

void Editor::handleEvents(SDL_Event& e)
{
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
		switch (e.key.keysym.sym) {
			case SDLK_TAB:
				togglePallete();
				break;
			case SDLK_a:
				camMoveDir = -1;
				break;
			case SDLK_d:
				camMoveDir = 1;
				break;
			default:
				break;
		}
	}
	if (e.type == SDL_KEYUP && e.key.repeat == 0) {
		switch (e.key.keysym.sym) {
			case SDLK_a:
				camMoveDir = 0;
				break;
			case SDLK_d:
				camMoveDir = 0;
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
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_Rect* box = new SDL_Rect{ mouse->getPixelPosition().x, 
                                  mouse->getPixelPosition().y, 8, 8 };
	SDL_RenderDrawRect(renderer, box);

	delete box;
	box = nullptr;
}

void Editor::renderMousePos()
{
	updatePosTexture(mouse->getTilePosition());
	mousePosTexture->render(1, 1);
}

void Editor::updatePosTexture(Vec2 position)
{
	if (mousePosTexture != nullptr) {
		mousePosTexture->free();
	}
	mousePosTexture = new Texture(renderer, 
		std::to_string((int)round(position.x)) + ", " + 
		std::to_string((int)round(position.y)), font, fontColor, 15, 5);
}

void Editor::moveCamera(int dir)
{
	SDL_Rect* camera = scene->getCamera();
	camera->x += dir;
	if (camera->x < 0) {
		camera->x = 0;
	}
	else if (camera->x > 320) {
		camera->x = 320;
	}
}

void Editor::writeTileToMap(Vec2 tile)
{
}
