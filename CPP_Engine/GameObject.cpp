#include <iostream>
#include "GameObject.h"
#include "Utils.h"
using namespace std;

// TODO - Move physics, collision and movement to Player class

GameObject::GameObject()
{
	name = "";
	texture = nullptr;
	currentPosition = { 0, 0 };
	currentVelocity = { 0, 0 };
	physics = nullptr;
	collider = nullptr;
	colliding = false;

	currentState = AIRBORNE;
}

GameObject::GameObject(string n, axes p, Texture* t)
{
	cout << "creating gobj " << n << "\n";
	name = n;
	texture = t;
	currentPosition = p;
	currentVelocity = { 0, 0 };
	physics = nullptr;
	collider = nullptr;
	colliding = false;

	currentState = AIRBORNE;
}

GameObject::GameObject(string n, axes p, Texture* t, bool ph)
{
	cout << "creating gobj " << n << "\n";
	name = n;
	texture = t;
	currentPosition = p;
	currentVelocity = { 0, 0 };
	physics = ph ? new Physics() : nullptr;
	collider = nullptr;
	colliding = false;
	
	currentState = AIRBORNE;
}

GameObject::GameObject(string n, axes p, Texture* t, bool ph, bool c)
{
	cout << "creating gobj " << n << "\n";
	name = n;
	texture = t;
	currentPosition = p;
	currentVelocity = { 0, 0 };
	physics = ph ? new Physics() : nullptr;
	collider = c ? new SDL_Rect { currentPosition.x, currentPosition.y, texture->getWidth(), texture->getHeight() } : nullptr;
	colliding = false;

	currentState = AIRBORNE;
}


GameObject::GameObject(const GameObject& src)
{
	name = src.name;
	texture = src.texture;
	currentPosition = src.currentPosition;
	currentVelocity = src.currentVelocity;
	physics = src.physics;
	collider = src.collider;
	colliding = src.colliding;

	currentState = src.currentState;
}

GameObject::~GameObject()
{
	cout << "destroying gobj " << name << "\n";

	if (texture != nullptr)
	{
		delete texture;
		texture = nullptr;
	}
	if (physics != nullptr)
	{
		delete physics;
		physics = nullptr;
	}
	if (collider != nullptr)
	{
		delete collider;
		collider = nullptr;
	}
}

void GameObject::render(int x, int y)
{
	texture->render(x, y);
}

void GameObject::handleEvent(SDL_Event& e)
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

void GameObject::moveColliders(float deltaTime)
{
	float xMovement = currentVelocity.x * deltaTime * speed;
	float yMovement = currentVelocity.y * deltaTime * speed;

	if (hasCollider())
	{
		collider->x += xMovement;
		collider->y += yMovement;
	}
}

void GameObject::move(float deltaTime)
{
	float xMovement = currentVelocity.x * deltaTime * speed;
	float yMovement = currentVelocity.y * deltaTime * speed;

	if (hasCollider())
	{
		if (!isColliding())
		{
			currentPosition.x += xMovement;
			currentPosition.y += yMovement;
		}
		collider->y = currentPosition.y;
		collider->x = currentPosition.x;
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

bool GameObject::hasPhysics()
{
	return physics != nullptr;
}

Physics* GameObject::getPhysics()
{
	return physics;
}

SDL_Rect* GameObject::getCollider()
{
	return collider;
}

bool GameObject::hasCollider()
{
	return collider != nullptr;
}

bool GameObject::isColliding()
{
	return colliding;
}

void GameObject::setColliding(bool c)
{
	colliding = c;
}
