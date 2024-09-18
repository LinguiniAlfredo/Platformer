#include "Box.h"
#include "Scene.h"
#include "Entity.h"
#include "Pickup.h"
#include "Components/Texture.h"

#include <iostream>
#include <string>

Box::Box(Scene* s, std::string path, Pickup* i, Vec2 pos)
{
	std::cout << "creating box \n";
	scene = s;
	currentPosition = pos;
	item = i;
	texture = new Texture(scene->getRenderer(), path);
	collider = new SDL_Rect{ currentPosition.x, currentPosition.y + 1, texture->getWidth(), texture->getHeight() };
}

Box::~Box()
{
	std::cout << "destroying box\n";
	delete texture;
	delete collider;
	texture = nullptr;
	collider = nullptr;

	if (item != nullptr)
	{
		delete item;
		item = nullptr;
	}
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
	// Check collisions on player from bottom
	for (Entity* ent : scene->getEntities())
	{
		if (ent->hasCollider() && ent->hasPhysics())
		{
			if (SDL_HasIntersection(collider, ent->getCollider()) && ent->getPosition().y > currentPosition.y)
			{
				colliding = true;
				if (currentState == FULL)
					openBox();
				break;
			}
			else
			{
				colliding = false;
			}
		}
	}
}

void Box::openBox()
{
	// reveal item in box and change texture to empty
	revealItem();
	setTexture("resources/textures/box_empty.png");
	currentState = EMPTY;
}

void Box::revealItem()
{
	item->setPosition(currentPosition.x, currentPosition.y - scene->getTileSize());
	scene->addEntity(item);
	item = nullptr;
}

void Box::setTexture(std::string path)
{
	if (texture != nullptr)
	{
		delete texture;
		texture = nullptr;
	}
	texture = new Texture(scene->getRenderer(), path);
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

bool Box::isSolid()
{
	return solid;
}

Vec2 Box::getPosition()
{
	return currentPosition;
}