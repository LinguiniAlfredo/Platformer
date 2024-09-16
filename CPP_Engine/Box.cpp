#include "Box.h"
#include "Components/Texture.h"
#include "Scene.h"
#include "Entity.h"

#include <iostream>
#include <string>

Box::Box(SDL_Renderer* renderer)
{
	std::cout << "creating box \n";
	currentPosition = { 0, 0 };
	texture = new Texture(renderer, textureFile);
	collider = new SDL_Rect{ currentPosition.x, currentPosition.y, texture->getWidth(), texture->getHeight() };
}

Box::Box(SDL_Renderer* renderer, std::string path, Vec2 pos)
{
	std::cout << "creating box \n";
	currentPosition = pos;
	texture = new Texture(renderer, path);
	collider = new SDL_Rect{ currentPosition.x, currentPosition.y, texture->getWidth(), texture->getHeight() };
}

Box::~Box()
{
	std::cout << "destroying box\n";
	delete texture;
	texture = nullptr;
	delete collider;
	collider = nullptr;
}

void Box::draw()
{
	texture->render(currentPosition.x, currentPosition.y);
}

void Box::update(float deltaTime)
{
	checkCollisions(deltaTime);
}

void Box::checkCollisions(float deltaTime)
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

void Box::setScene(Scene* s)
{
	scene = s;
}

bool Box::isColliding()
{
	return colliding;
}

bool Box::hasCollider()
{
	return collider != nullptr;
}

SDL_Rect* Box::getCollider()
{
	return collider;
}

Vec2 Box::getPosition()
{
	return currentPosition;
}