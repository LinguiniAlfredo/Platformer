#include "Surface.h"
#include "Scene.h"
#include "Entity.h"
#include "Components/Texture.h"

#include <iostream>
#include <string>

Surface::Surface(Scene* s)
{
	printf("creating surface \n");
	scene = s;
	currentPosition = { 0, 0 };
	texture = new Texture(scene->getRenderer(), textureFile);
	collider = new SDL_Rect{ currentPosition.x, currentPosition.y, texture->getWidth(), texture->getHeight() };
}

Surface::Surface(Scene* s, string path, Vec2 pos)
{
	printf("creating surface \n");
	scene = s;
	currentPosition = pos;
	texture = new Texture(scene->getRenderer(), path);
	collider = new SDL_Rect{ currentPosition.x, currentPosition.y, texture->getWidth(), texture->getHeight() };
}

Surface::~Surface()
{
	printf("destroying surface\n");
	delete texture;
	delete collider;
	texture = nullptr;
	collider = nullptr;
}

void Surface::draw()
{
	texture->render(currentPosition.x, currentPosition.y);
}

void Surface::update(float deltaTime)
{
	checkCollisions(deltaTime);
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

Vec2 Surface::getPosition()
{
	return currentPosition;
}