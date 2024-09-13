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


void GameObject::move(float deltaTime)
{
	//if (physics != nullptr)
	//{
	//	if (currentState == AIRBORNE)
	//	{
	//		currentPosition.y += physics->getGravity();
	//	}
	//}

	if (hasCollider())
	{
		collider->x += currentVelocity.x * deltaTime * speed;
		collider->x = clamp(collider->x, 0 - (texture->getWidth() / 2), 640 - (texture->getWidth() / 2));

		collider->y += currentVelocity.y * deltaTime * speed;
		collider->y = clamp(collider->y, 0 - (texture->getHeight() / 2), 480 - (texture->getHeight() / 2));

		currentPosition.x = collider->x;
		currentPosition.y = collider->y;
	}
	else
	{
		currentPosition.x += currentVelocity.x * deltaTime * speed;
		currentPosition.x = clamp(currentPosition.x, 0 - (texture->getWidth() / 2), 640 - (texture->getWidth() / 2));

		currentPosition.y += currentVelocity.y * deltaTime * speed;
		currentPosition.y = clamp(currentPosition.y, 0 - (texture->getHeight() / 2), 480 - (texture->getHeight() / 2));
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

