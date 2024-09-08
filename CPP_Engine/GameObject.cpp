#include "GameObject.h"
using namespace std;

GameObject::GameObject()
{
	name = "";
	width = 0;
	height = 0;
	texture = NULL;
	scaledSize = NULL;
	position = { 0,0 };
}

GameObject::GameObject(string n, double w, double h, coordinates p, SDL_Texture* t)
{
	name = n;
	width = w;
	height = h;
	texture = t;
	position = p;

	SDL_Rect* size = new SDL_Rect();
	size->x = p.x;
	size->y = p.y;
	size->w = w;
	size->h = h;
	scaledSize = size;
}

GameObject::GameObject(const GameObject& src)
{
	name = src.name;
	width = src.width;
	height = src.height;
	texture = src.texture;
	position = src.position;
	scaledSize = src.scaledSize;
}

GameObject::~GameObject()
{
	SDL_DestroyTexture(texture);
	texture = NULL;
	delete scaledSize;
	scaledSize = NULL;
}

double GameObject::getWidth()
{
	return width;
}

double GameObject::getHeight()
{
	return height;
}

string GameObject::getName()
{
	return name;
}

coordinates GameObject::getPosition()
{
	return position;
}

SDL_Texture* GameObject::getTexture()
{
	return texture;
}

SDL_Rect* GameObject::getSize()
{
	return scaledSize;
}
