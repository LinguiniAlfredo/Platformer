#include "Pickup.h"
#include "../Scene.h"
#include "Player.h"
#include "../Components/Texture.h"
#include "../Components/Physics.h"
#include "../Components/Collision.h"

#include <iostream>
#include <string>

Pickup::Pickup(Scene* scene, std::string itemType, bool physics)
{
	//std::cout << "creating pickup \n";
	this->scene = scene;
	this->type = itemType;
	this->currentPosition = { 0,0 };
	this->texture = new Texture(scene->getRenderer(), "resources/textures/" + itemType + ".png");
	this->collider = new Collision(scene->getRenderer(), currentPosition.x, currentPosition.y, texture->getWidth(), texture->getHeight());
	this->physics = nullptr;
	if (physics) {
		this->physics = new Physics();
	}
	this->solid = false;
}

Pickup::Pickup(Scene* scene, std::string itemType, Vec2 pos, bool physics)
{
	//std::cout << "creating pickup \n";
	this->scene = scene;
	this->type = itemType;
	this->currentPosition = pos;
	this->texture = new Texture(scene->getRenderer(), "resources/textures/" + itemType + ".png");
	this->collider = new Collision(scene->getRenderer(), currentPosition.x, currentPosition.y, texture->getWidth(), texture->getHeight());
	this->physics = nullptr;
	if (physics) {
		this->physics = new Physics();
	}
	this->solid = false;

}

Pickup::~Pickup()
{
	//std::cout << "destroying pickup\n";
	delete texture;
	delete collider;
	texture = nullptr;
	collider = nullptr;

	if (physics) {
		delete physics;
		physics = nullptr;
	}
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

	collider->getBox()->x = currentPosition.x;
	collider->getBox()->y = currentPosition.y;

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
				currentPosition.x + collider->getBox()->w >= ent->getPosition().x && currentPosition.x < ent->getPosition().x + ent->getCollider()->getBox()->w)
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
		if (SDL_HasIntersection(collider->getBox(), player->getCollider()->getBox())) {
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
		collider->getBox()->y += currentVelocity.y * deltaTime;
		currentPosition.y += currentVelocity.y * deltaTime;
		if (currentState != GROUNDED) {
			currentVelocity.y += physics->getGravity();
		}

		for (Entity* ent : scene->getEntities()) {
			if (ent->hasCollider() && ent != this) {
				if (SDL_HasIntersection(collider->getBox(), ent->getCollider()->getBox()) && ent->isSolid()) {
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