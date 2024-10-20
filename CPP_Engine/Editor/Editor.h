#include <SDL.h>
class Pallete;
class Mouse;

class Editor
{
public:
	Editor(SDL_Renderer* renderer);
	~Editor();

	void update();
	void handleEvents(SDL_Event& e);
	void togglePallete();

	SDL_Renderer* getRenderer();
	Pallete* getPallete();
	Mouse* getMouse();

private:
	SDL_Renderer* renderer;
	Pallete* pallete;
	Mouse* mouse;

	bool palleteOpen = false;

	void highlightHoveredTiles();
};