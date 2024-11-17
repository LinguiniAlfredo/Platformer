#pragma once
#include <string>
#include <SDL.h>
#include <SDL_ttf.h>

using namespace std;

class Texture
{
public:
	Texture();
	Texture(SDL_Renderer* renderer);
	Texture(SDL_Renderer* renderer, string path);
	Texture(SDL_Renderer* renderer, string path, int width, int height);
	Texture(SDL_Renderer* r, string text, TTF_Font* font, SDL_Color color, int w, int h);
	~Texture();

	void free();
	void render(int x, int y);

	int getWidth();
	int getHeight();

	SDL_Texture* getTexture();

    string name = "";


private:
	SDL_Texture* texture;
	SDL_Renderer* renderer;

	SDL_Texture* loadFromFile(string path);
	SDL_Texture*  loadFromRenderedText(string text, TTF_Font* font, SDL_Color color);
	int width;
	int height;

};

