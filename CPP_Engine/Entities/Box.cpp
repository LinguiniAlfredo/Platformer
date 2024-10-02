#include <iostream>
#include <string>

#include "Box.h"
#include "Entity.h"
#include "Pickup.h"
#include "../Scene.h"
#include "../Components/Texture.h"
#include "../Components/Collision.h"

Box::Box(Scene* s, Pickup* i, Vec2 pos)
{
	//std::cout << "creating box \n";
	scene = s;
	currentPosition = pos;
	item = i;
	texture = new Texture(scene->getRenderer(), textureFile);
	collider = new Collision(scene->getRenderer(), currentPosition.x, currentPosition.y + 1, texture->getWidth(), texture->getHeight());

	currentState = item == nullptr;
}

Box::~Box()
{
	//std::cout << "destroying box\n";
	delete texture;
	delete collider;
	texture = nullptr;
	collider = nullptr;

	if (item != nullptr) {
		delete item;
		item = nullptr;
	}
}

void Box::checkCollisions(float deltaTime)
{
	// Check collisions on player from bottom
	for (Entity* ent : scene->getEntities()) {
		if (ent->hasCollider() && ent->hasPhysics()) {
			if (SDL_HasIntersection(collider->getBox(), ent->getCollider()->getBox()) && ent->getPosition().y > currentPosition.y) {
				colliding = true;
				if (currentState == FULL) {
					openBox();
				}
				break;
			}
			else {
				colliding = false;
			}
		}
	}
}

void Box::openBox()
{
	revealItem();
	setTexture("resources/textures/box_empty.png");
	currentState = EMPTY;
}

void Box::revealItem()
{
	item->setPosition(currentPosition.x, currentPosition.y - scene->getTileSize());
	item->setColliderPosition(currentPosition.x, currentPosition.y - scene->getTileSize());
	scene->addEntity(item);
	item = nullptr;
}
