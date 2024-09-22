#include "Collision.h"
#include "Texture.h"

Collision::Collision(SDL_Renderer* renderer, int x, int y, int w, int h)
{
	this->renderer = renderer;
	this->box = new SDL_Rect{ x, y, w, h };

	this->collidingTexture = new Texture(renderer, "resources/textures/collision_red.png");
	this->notCollidingTexture= new Texture(renderer, "resources/textures/collision_green.png");
}

Collision::~Collision()
{
	delete box;
	delete collidingTexture;
	delete notCollidingTexture;
	box = nullptr;
	collidingTexture = nullptr;
	notCollidingTexture = nullptr;
}

void Collision::render(bool colliding)
{
	if (colliding) {
		collidingTexture->render(box->x, box->y);
	}
	else {
		notCollidingTexture->render(box->x, box->y);
	}
}

SDL_Rect* Collision::getBox()
{
	return box;
}