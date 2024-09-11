#include <iostream>
#include "GameObject.h"
using namespace std;

GameObject::GameObject()
{
	name = "";
	texture = nullptr;
	currentPosition = { 0, 0 };
	currentVelocity = { 0, 0 };
}

GameObject::GameObject(string n, axes p, Texture* t)
{
	cout << "creating gobj " << n << "\n";
	name = n;
	texture = t;
	currentPosition = p;
	currentVelocity = { 0, 0 };
}

GameObject::GameObject(const GameObject& src)
{
	name = src.name;
	texture = src.texture;
	currentPosition = src.currentPosition;
	currentVelocity = src.currentVelocity;
}

GameObject::~GameObject()
{
	cout << "destroying gobj " << name << "\n";
	delete texture;
	texture = nullptr;
}

void GameObject::render(int x, int y)
{
	texture->render(x, y);
}

// TODO - Needs smooth, time-based movement
void GameObject::handleEvent(SDL_Event& e)
{
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_a: 
			currentVelocity.x -= velocity;
			break;
		case SDLK_d:
			currentVelocity.x += velocity;
			break;
		case SDLK_w:
			currentVelocity.y -= velocity;
			break;
		case SDLK_s:
			currentVelocity.y += velocity;
			break;
		}
	} 
	else if (e.type == SDL_KEYUP && e.key.repeat == 0)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_a:
			currentVelocity.x += velocity;
			break;
		case SDLK_d:
			currentVelocity.x -= velocity;
			break;
		case SDLK_w:
			currentVelocity.y += velocity;
			break;
		case SDLK_s:
			currentVelocity.y -= velocity;
			break;
		}
	}
	move();
}

void GameObject::move()
{
	currentPosition.x += currentVelocity.x;
	if (currentPosition.x <= (0 - texture->getWidth()/2) || currentPosition.x >= (640 - texture->getWidth()/2))
	{
		currentPosition.x -= currentVelocity.x;
	}

	currentPosition.y += currentVelocity.y;
	if (currentPosition.y <= (0 - texture->getHeight()/2) || currentPosition.y >= (480 - texture->getHeight()/2))
	{
		currentPosition.y -= currentVelocity.y;

	}
}

string GameObject::getName()
{
	return name;
}

axes GameObject::getPosition()
{
	return currentPosition;
}

Texture* GameObject::getTexture()
{
	return texture;
}
