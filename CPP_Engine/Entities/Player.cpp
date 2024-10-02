#include <iostream>
#include <cmath>
#include "Player.h"
#include "../Scene.h"
#include "../Components/Texture.h"
#include "../Components/Physics.h"
#include "../Components/Collision.h"

void Player::update(float deltaTime)
{
	checkForFloor();
	checkCollisions(deltaTime);
	move(deltaTime);
}

void Player::handleEvent(SDL_Event& e)
{
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
		SDL_Keycode key = e.key.keysym.sym;
		if (key == SDLK_a) {
			currentVelocity.x = -1;
		}
		if (key == SDLK_d) {
			currentVelocity.x = 1;
		}
		if (key == SDLK_SPACE && currentState == GROUNDED) {
			currentVelocity.y = -1 * jumpForce;
			currentState = AIRBORNE;
		}
		if (key == SDLK_LSHIFT && currentVelocity.x != 0) {
			running = true;
		}

	}
	if (e.type == SDL_KEYUP && e.key.repeat == 0) {
		SDL_Keycode key = e.key.keysym.sym;
		if (key == SDLK_a) {
			if (currentVelocity.x < 0)
				currentVelocity.x = 0;
		}
		if (key == SDLK_d) {
			if (currentVelocity.x > 0)
				currentVelocity.x = 0;
		}
		if (key == SDLK_SPACE) {
			currentVelocity.y /= 2;
		}
		if (key == SDLK_LSHIFT) {
			running = false;
		}
	}
}

void Player::checkForFloor()
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

// move collider where player will be next frame and check collisions.
void Player::checkCollisions(float deltaTime)
{
	collider->getBox()->x += static_cast<int>(round(currentVelocity.x * deltaTime * groundSpeed));
	collider->getBox()->y += static_cast<int>(round(currentVelocity.y * deltaTime));

	if (currentState != GROUNDED) {
		static_cast<int>(round(currentVelocity.y += physics->getGravity()));
	}

	for (Entity* ent : scene->getEntities()) {
		if (ent->hasCollider() && ent != this) {
			if (SDL_HasIntersection(collider->getBox(), ent->getCollider()->getBox()) && ent->isSolid()) {
				colliding = true;
				if (ent->getPosition().y > currentPosition.y) {
					currentState = GROUNDED;
				}
				resolveCollision(ent);

				break;
			}
			else {
				colliding = false;
			}
		}
	}

}

void Player::resolveCollision(Entity* ent)
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

void Player::move(float deltaTime)
{
	// Position += Velocity
	// Velocity += Acceleration
	static int currentDir;
	float speedX = currentVelocity.x * deltaTime * groundSpeed;
	float speedY = currentVelocity.y * deltaTime;

	if (!colliding) {
		currentPosition.x += (int)round(speedX);
		currentPosition.y += (int)round(speedY);

		if (currentState != GROUNDED) {
			currentVelocity.y += (int)round(physics->getGravity());
		}

	/*	if (running && abs(currentVelocity.x) < maxRunSpeed) {
			currentVelocity.x += runAccel;
		}
		else if (!running && abs(currentVelocity.x) > minRunSpeed) {
			currentVelocity.x -= runAccel;
		}*/
	}

	collider->getBox()->x = currentPosition.x;
	collider->getBox()->y = currentPosition.y;

	// kill player if falls below floor
	if (currentPosition.y > 180) {
		scene->removeEntity(this);
	}

	//// reset groundSpeed if changing direction
	//if (currentDir != currentVelocity.x) {
	//	groundSpeed = minRunSpeed;
	//}
	//currentDir = currentVelocity.x;
}

void Player::setPowerLevel(int p)
{
	power += p;
	if (texture != nullptr) {
		delete texture;
		texture = nullptr;
	}

	switch (power) {
		case FLOWER:
			texture = new Texture(scene->getRenderer(), "resources/textures/guy_flower.png");
			// add some power logic
			break;
		case NONE:
			texture = new Texture(scene->getRenderer(), "resources/textures/guy.png");
			break;
		default:
			scene->removeEntity(this);
			//scene->respawnPlayer();
			break;
	}
}