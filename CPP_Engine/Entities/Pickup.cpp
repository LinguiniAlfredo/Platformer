#include "Pickup.h"
#include "Scene.h"
#include "Player.h"
#include "Components/Texture.h"
#include "Components/Physics.h"

#include <iostream>
#include <string>

Pickup::Pickup(Scene* s, std::string itemType, bool physics)
{
	std::cout << "creating pickup \n";
	scene = s;
	type = itemType;
	currentPosition = { 0,0 };
	texture = new Texture(scene->getRenderer(), "resources/textures/" + itemType + ".png");
	collider = new SDL_Rect{ currentPosition.x, currentPosition.y, texture->getWidth(), texture->getHeight() };
	this->physics = nullptr;
	if (physics) {
		this->physics = new Physics();
	}
}

Pickup::Pickup(Scene* s, std::string itemType, Vec2 pos, bool physics)
{
	std::cout << "creating pickup \n";
	scene = s;
	type = itemType;
	currentPosition = pos;
	texture = new Texture(scene->getRenderer(), "resources/textures/" + itemType + ".png");
	collider = new SDL_Rect{ currentPosition.x, currentPosition.y, texture->getWidth(), texture->getHeight() };
	this->physics = nullptr;
	if (physics) {
		this->physics = new Physics();
	}
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
	checkForFloor();
	checkCollisions(deltaTime);
	if (physics) {
		move(deltaTime);
	}
}

void Pickup::move(float deltaTime)
{
	if (!colliding && currentState != GROUNDED) {
		currentVelocity.y += physics->getGravity();
	}

	collider->x = currentPosition.x;
	collider->y = currentPosition.y;

	// kill if falls below floor
	if (currentPosition.y > 180) {
		scene->removeEntity(this);
	}
}

void Pickup::checkForFloor()
{
	if (currentState == GROUNDED) {
		for (Entity* ent : scene->getEntities()) {
			if (ent->isSolid() && ent->getPosition().y - currentPosition.y == scene->getTileSize() &&
				currentPosition.x + collider->w >= ent->getPosition().x && currentPosition.x < ent->getPosition().x + ent->getCollider()->w)
			{
				return;
			}

		}
		currentState = AIRBORNE; // if nothing underneath player, set AIRBORNE
	}
}

void Pickup::checkCollisions(float deltaTime)
{
	// Check collisions on player
	Player* player = dynamic_cast<Player*>(scene->getPlayer());
	if (player != nullptr) {
		if (SDL_HasIntersection(collider, player->getCollider())) {
			colliding = true;
			if (type == "flower") {
				player->setPowerLevel(1);
			}
			if (type == "skull") {
				player->setPowerLevel(-1);
			}
		}
		else {
			colliding = false;
		}

		if (colliding) {
			scene->removeEntity(this);
		}
	}

	if (physics) {
		collider->y += currentVelocity.y * deltaTime;
		currentPosition.y += currentVelocity.y * deltaTime;
		if (currentState != GROUNDED) {
			currentVelocity.y += physics->getGravity();
		}

		for (Entity* ent : scene->getEntities()) {
			if (ent->hasCollider() && ent != this) {
				if (SDL_HasIntersection(collider, ent->getCollider()) && ent->isSolid()) {
					colliding = true;
					resolveCollision(ent);

					if (ent->getPosition().y > currentPosition.y) {
						currentState = GROUNDED;
					}
					break;
				}
				else {
					colliding = false;
				}
			}
		}
	}
}

void Pickup::resolveCollision(Entity* ent)
{
	// if collision below player and y velocity is positive
	if (currentVelocity.y > 0 && ent->getPosition().y > currentPosition.y) {
		currentPosition.y = ent->getPosition().y - scene->getTileSize();
		currentVelocity.y = 0;
	}
	// if collision above player and y velocity is negative
	if (currentVelocity.y < 0 && ent->getPosition().y < currentPosition.y) {
		currentPosition.y = ent->getPosition().y + scene->getTileSize();
		currentVelocity.y = 0;
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
