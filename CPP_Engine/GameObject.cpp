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
	collider = c ? new Collision(currentPosition, texture->getWidth(), texture->getHeight()) : nullptr;

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

void GameObject::render(float x, float y)
{
	texture->render((int)x, (int)y);
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
		
	}
}


void GameObject::move(float deltaTime)
{
	if (physics != nullptr)
	{
		if (currentState == AIRBORNE)
		{
			currentPosition.y += physics->getGravity();
		}
	}

	currentPosition.x += currentVelocity.x * deltaTime * speed;
	currentPosition.x = clamp(currentPosition.x, 0.f - (texture->getWidth() / 2.f), 640.f - (texture->getWidth() / 2.f));

	currentPosition.y += currentVelocity.y * deltaTime * speed;
	currentPosition.y = clamp(currentPosition.y, 0.f - (texture->getHeight() / 2.f), 480.f - (texture->getHeight() / 2.f));

	 //do this before moving actual object to check collisions first
	if (collider != nullptr)
	{
		collider->setPosition(currentPosition);
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

bool GameObject::hasCollider()
{
	return collider != nullptr;
}

Collision* GameObject::getCollider()
{
	return collider;
}

