#include "Surface.h"
#include "Texture.h"
#include "Scene.h"
#include "Entity.h"

#include <iostream>
#include <string>

Surface::Surface(SDL_Renderer* renderer)
{
	std::cout << "creating surface \n";
	currentPosition = { 200, 350 };
	texture = new Texture(renderer, textureFile);
	collider = new SDL_Rect{ currentPosition.x, currentPosition.y, texture->getWidth(), texture->getHeight() };
}

Surface::Surface(SDL_Renderer* renderer, string path, vec2 pos)
{
	std::cout << "creating surface \n";
	currentPosition = pos;
	texture = new Texture(renderer, path);
	collider = new SDL_Rect{ currentPosition.x, currentPosition.y, texture->getWidth(), texture->getHeight() };
}

Surface::~Surface()
{
	std::cout << "destroying surface\n";
	delete texture;
	texture = nullptr;
	delete collider;
	collider = nullptr;
}

void Surface::update(float deltaTime)
{
	checkCollisions(deltaTime);
}

void Surface::draw()
{
	texture->render(currentPosition.x, currentPosition.y);
}

void Surface::checkCollisions(float deltaTime)
{
	// Check collisions on all other entities
	for (Entity* ent : scene->getEntities())
	{
		if (ent->hasCollider() && ent != this)
		{
			if (SDL_HasIntersection(collider, ent->getCollider()))
			{
				colliding = true;
				break;
			}
			else
			{
				colliding = false;
			}
		}
	}
}

void Surface::setScene(Scene* s)
{
	scene = s;
}

bool Surface::isColliding()
{
	return colliding;
}

bool Surface::hasCollider()
{
	return collider != nullptr;
}

SDL_Rect* Surface::getCollider()
{
	return collider;
}

vec2 Surface::getPosition()
{
	return currentPosition;
}