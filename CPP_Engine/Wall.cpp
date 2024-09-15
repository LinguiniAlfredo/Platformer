#include "Wall.h"
#include "Texture.h"
#include "Scene.h"
#include "Entity.h"
#include <iostream>

Wall::Wall(SDL_Renderer* renderer)
{
	std::cout << "creating wall \n";
	currentPosition = { 300, 200 };
	texture = new Texture(renderer, textureFile, 20, 200);
	collider = new SDL_Rect{ currentPosition.x, currentPosition.y, texture->getWidth(), texture->getHeight() };
}

Wall::~Wall()
{
	std::cout << "destroying wall\n";
	delete texture;
	texture = nullptr;
	delete collider;
	collider = nullptr;
}

void Wall::update(float deltaTime)
{
	checkCollisions(deltaTime);
}

void Wall::draw()
{
	texture->render(currentPosition.x, currentPosition.y);
}

void Wall::checkCollisions(float deltaTime)
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

void Wall::setScene(Scene* s)
{
	scene = s;
}

bool Wall::isColliding()
{
	return colliding;
}

bool Wall::hasCollider()
{
	return collider != nullptr;
}

SDL_Rect* Wall::getCollider()
{
	return collider;
}