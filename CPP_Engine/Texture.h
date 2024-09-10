#pragma once
#include <string>
#include <SDL.h>

using namespace std;

class Texture
{
public:
	Texture();
	Texture(SDL_Renderer* renderer);
	Texture(SDL_Renderer* renderer, string path);
	~Texture();

	void free();
	void render(int x, int y);

	int getWidth();
	int getHeight();

	SDL_Texture* getTexture();

private:
	SDL_Texture* texture;
	SDL_Renderer* renderer;
	SDL_Texture* loadFromFile(string path);

	int width;
	int height;

};

