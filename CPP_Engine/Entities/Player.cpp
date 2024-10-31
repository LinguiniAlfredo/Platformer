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
	moveCamera();
}

void Player::handleEvent(SDL_Event& e)
{
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
		SDL_Keycode key = e.key.keysym.sym;
		if (key == SDLK_a) {
			velocity.x = -1; //-runAccel;
		}
		if (key == SDLK_d) {
			velocity.x = 1; //runAccel;
		}
		if (key == SDLK_SPACE && currentState == GROUNDED) {
			velocity.y = -1.0f * jumpForce;
			currentState = AIRBORNE;
		}
		if (key == SDLK_LSHIFT) {
			maxSpeed = 1.7f;
			running = true;
		}

	}
	if (e.type == SDL_KEYUP && e.key.repeat == 0) {
		SDL_Keycode key = e.key.keysym.sym;
		if (key == SDLK_a) {
			if (velocity.x < 0) {
				velocity.x = 0;
			}
		}
		if (key == SDLK_d) {
			if (velocity.x > 0) {
				velocity.x = 0;
			}
		}
		if (key == SDLK_SPACE) {
			velocity.y /= 2;
		}
		if (key == SDLK_LSHIFT) {
			maxSpeed = 1;
			running = false;
		}
	}
}

void Player::checkForFloor()
{
	if (currentState == GROUNDED) {
		for (Entity* ent : scene->getEntities()) {
			if (ent->isSolid() && ent->getPosition().y - actualPosition.y == scene->getTileSize() &&
				actualPosition.x + collider->getBox()->w >= ent->getPosition().x && actualPosition.x < ent->getPosition().x + ent->getCollider()->getBox()->w)
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
	collider->getBox()->x += static_cast<int>(round(velocity.x * deltaTime));
	collider->getBox()->y += static_cast<int>(round(velocity.y * deltaTime));

	if (currentState != GROUNDED) {
		velocity.y += physics->getGravity();
	}

	for (Entity* ent : scene->getEntities()) {
		if (ent->hasCollider() && ent != this) {
			if (SDL_HasIntersection(collider->getBox(), ent->getCollider()->getBox()) && ent->isSolid()) {
				colliding = true;
				if (ent->getPosition().y > actualPosition.y) {
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
	if (velocity.y > 0 && ent->getPosition().y > actualPosition.y) {
		actualPosition.y = static_cast<float>(
                ent->getPosition().y - scene->getTileSize());
		//currentVelocity.y = 0;
	}
	// if collision above player and y velocity is negative
	if (velocity.y < 0 && ent->getPosition().y < actualPosition.y) {
		actualPosition.y = static_cast<float>(
                ent->getPosition().y + scene->getTileSize());
		velocity.y = 0;
	}
}

void Player::move(float deltaTime)
{
	float speedY = velocity.y * deltaTime;

	if (!colliding) {
		actualPosition.x += velocity.x;
		/*if (abs(velocity.x) < maxSpeed) {
			if (velocity.x > 0)
				velocity.x += runAccel;
			else if (velocity.x < 0)
				velocity.x -= runAccel;
		}
		else if (abs(velocity.x) > maxSpeed) {
			if (velocity.x > 0)		 
				velocity.x -= runAccel;
			else if (velocity.x < 0)	 
				velocity.x += runAccel;
		}*/
	}

	if (currentState != GROUNDED) {
		actualPosition.y += (int)round(speedY);
		velocity.y += (int)round(physics->getGravity());
	} else {
		velocity.y = 0;
	}

	position.x = static_cast<int>(round((actualPosition.x)));
	position.y = static_cast<int>(round((actualPosition.y)));
	collider->getBox()->x = position.x;
	collider->getBox()->y = position.y;

	// kill player if falls below floor
	if (actualPosition.y > 180) {
		scene->removeEntity(this);
	}
}

void Player::moveCamera()
{
	SDL_Rect* camera = scene->getCamera();
	int center = (camera->x + camera->w) / 2;
	if (position.x > center) 
	{
		camera->x = position.x - camera->w / 2;
	}
}

void Player::setPowerLevel(int p)
{
	power += p;
	switch (power) {
		case FLOWER:
			// TODO - add power-up animation
			setTexture("resources/textures/guy_flower.png");
			break;
		case NONE:
			// TODO - add power-down animation
			setTexture("resources/textures/guy.png");
			break;
		default:
			scene->removeEntity(this);
			//scene->respawnPlayer();
			break;
	}
}

void Player::incrementCoinCount()
{
	coinCount++;
}
