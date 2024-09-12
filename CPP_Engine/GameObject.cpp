#include <iostream>
#include "GameObject.h"
#include "Utils.h"
using namespace std;

// TODO - move to keyboard class
enum keys {
	UP,
	DOWN,
	LEFT,
	RIGHT
};

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

void GameObject::handleEvent(SDL_Event& e, float deltaTime)
{
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{
		SDL_Keycode key = e.key.keysym.sym;
		if (key == SDLK_a)
		{
			currentVelocity.x = -1;
		}
		if (key == SDLK_d)
		{
			currentVelocity.x = 1;
		}
		if (key == SDLK_w)
		{
			currentVelocity.y = -1;
		}
		if (key == SDLK_s)
		{
			currentVelocity.y = 1;
		}
	} 
	if (e.type == SDL_KEYUP && e.key.repeat == 0)
	{
		SDL_Keycode key = e.key.keysym.sym;
		if (key == SDLK_a)
		{
			if (currentVelocity.x < 0)
				currentVelocity.x = 0;
		}
		if (key == SDLK_d)
		{
			if (currentVelocity.x > 0)
				currentVelocity.x = 0;
		}
		if (key == SDLK_w)
		{
			if (currentVelocity.y < 0)
				currentVelocity.y = 0;
		}
		if (key == SDLK_s)
		{
			if (currentVelocity.y > 0)
				currentVelocity.y = 0;
		}
	}
	
}


void GameObject::move(float deltaTime)
{

	currentPosition.x += currentVelocity.x * deltaTime * speed;
	currentPosition.x = clamp(currentPosition.x, 0 - (texture->getWidth() / 2), 640 - (texture->getWidth() / 2));

	currentPosition.y += currentVelocity.y * deltaTime * speed;
	currentPosition.y = clamp(currentPosition.y, 0 - (texture->getHeight() / 2), 480 - (texture->getHeight() / 2));
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
