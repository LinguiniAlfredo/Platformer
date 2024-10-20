#include "HUD.h"
#include <string>
#include "Components/Texture.h"
#include "Utils/Vec2.h"

HUD::HUD(SDL_Renderer* renderer)
{
	this->renderer = renderer;
	this->font = TTF_OpenFont("resources/fonts/nintendo-nes-font.ttf", 28);
	this->fps = new Texture(renderer, "0 FPS", font, color, 15,5);
}

HUD::~HUD()
{
	delete fps;
	fps = nullptr;

	TTF_CloseFont(font);
	font = nullptr;
}

void HUD::updateAndDraw(float fps)
{
	updateFPS(fps);
	this->fps->render(1, 1);
	//updateCoins()
	//updateLife()
	//this->coins->render
	//this->life->render
}

void HUD::updateFPS(float value)
{
	if (fps != nullptr) {
		fps->free();
	}
	fps = new Texture(renderer, std::to_string((int)round(value)) + " FPS", font, color, 15,5);
}