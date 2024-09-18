#include "Pickup.h"
#include "Scene.h"
#include "Entity.h"
#include "Components/Texture.h"

#include <iostream>
#include <string>

Pickup::Pickup(Scene* s, std::string itemType)
{
	std::cout << "creating pickup \n";
	scene = s;
	currentPosition = { 0,0 };
	texture = new Texture(scene->getRenderer(), "resources/textures/" + itemType + ".png");
	collider = new SDL_Rect{ currentPosition.x, currentPosition.y, texture->getWidth(), texture->getHeight() };
}

Pickup::Pickup(Scene* s, std::string itemType, Vec2 pos)
{
	std::cout << "creating pickup \n";
	scene = s;
	currentPosition = pos;
	texture = new Texture(scene->getRenderer(), "resources/textures/" + itemType + ".png");
	collider = new SDL_Rect{ currentPosition.x, currentPosition.y, texture->getWidth(), texture->getHeight() };
}

Pickup::~Pickup()
{
	std::cout << "destroying pickup\n";
	delete texture;
	delete collider;
	texture = nullptr;
	collider = nullptr;
}

void Pickup::draw()
{
	texture->render(currentPosition.x, currentPosition.y);
}

void Pickup::update(float deltaTime)
{
	checkCollisions(deltaTime);
}

void Pickup::checkCollisions(float deltaTime)
{
	// Check collisions on player
	for (Entity* ent : scene->getEntities())
	{
		if (ent->hasCollider() && ent->hasPhysics())
		{
			if (SDL_HasIntersection(collider, ent->getCollider()))
			{
				colliding = true;
			}
			else
			{
				colliding = false;
			}
		}
	}
	if (colliding)
	{
		scene->removeEntity(this);
	}
}


// TODO - These functions are in everything
//        Do I need to override them every time?

void Pickup::setScene(Scene* s)
{
	scene = s;
}

bool Pickup::isColliding()
{
	return colliding;
}

bool Pickup::hasCollider()
{
	return collider != nullptr;
}

SDL_Rect* Pickup::getCollider()
{
	return collider;
}

bool Pickup::isSolid()
{
	return solid;
}

Vec2 Pickup::getPosition()
{
	return currentPosition;
}

void Pickup::setPosition(int x, int y)
{
	currentPosition.x = x;
	currentPosition.y = y;
	collider->x = x;
	collider->y = y;
}