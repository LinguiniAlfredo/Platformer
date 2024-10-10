#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
class Player;
class Texture;

class HUD
{
public:
	HUD(SDL_Renderer* renderer);
	~HUD();

	void updateAndDraw(float fps);

private:
	SDL_Renderer* renderer;
	TTF_Font* font;
	Texture* fps;
	SDL_Color color = { 255,255,255,255 };

	void updateFPS(float value);
};

