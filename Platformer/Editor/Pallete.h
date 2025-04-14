#pragma once
#include <SDL.h>
class Texture;

class Pallete
{
public:
	Pallete(SDL_Renderer* renderer);
	~Pallete();

    Texture* texture;

	void update();
	void handleEvent(SDL_Event& e);

    int xPos = 0;
    int yPos = 32;
    int width = 32;
    int height = 64;
    
private:
	SDL_Renderer* renderer;
	SDL_Rect* box;
};
