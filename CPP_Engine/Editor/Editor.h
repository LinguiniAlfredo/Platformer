#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include "Utils/Vec2.h"
class Scene;
class Pallete;
class Texture;
class Mouse;

enum Tile {
	BLANK,
	GROUND
};

class Editor
{
public:
	Editor(SDL_Renderer* renderer, Scene* scene);
	~Editor();

	void update();
	void handleEvents(SDL_Event& e);
	void togglePallete();

	SDL_Renderer* getRenderer();
	Pallete* getPallete();
	Mouse* getMouse();

private:
	Scene* scene;
	SDL_Renderer* renderer;
	Pallete* pallete;
	TTF_Font* font;
	Mouse* mouse;
	Texture* mousePosTexture;
	SDL_Color fontColor = { 255,255,255,255 };

    bool tileUpdateable = true;
	int activeBrush = GROUND;
    Vec2 currentTile;

	bool palleteOpen = false;
	Vec2 initialCamPosition;
	int camMoveDir; 

	void highlightHoveredTiles(int color);
	void renderMousePos();
	void updatePosTexture(Vec2 position);
	void moveCamera(int dir);
	void writeTileToMap(Vec2 tile);

    bool mapChanged(int action);
    bool insidePallete();
};
