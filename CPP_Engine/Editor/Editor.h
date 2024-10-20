#include "Mouse.h"
#include <SDL.h>

class Editor
{
public:
	Editor(SDL_Renderer* renderer);
	~Editor();

	void update();
	void pollEvents(SDL_Event e);
	Mouse* getMouse();

private:
	SDL_Renderer* renderer;
	Mouse* mouse;

	void highlightHoveredTiles();
};