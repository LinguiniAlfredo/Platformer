#include <iostream>
#include <cmath>
#include "Player.h"
#include "Scene.h"
#include "Components/Texture.h"
#include "Components/Physics.h"
#include "Components/Collision.h"

Player::Player(Scene* s)
{
	//printf("creating player \n");
	scene = s;
	currentVelocity = { 0,0 };
	currentPosition = { 0,0 };
	texture = new Texture(scene->getRenderer(), textureFile);
	collider = new Collision (scene->getRenderer(), currentPosition.x, currentPosition.y, texture->getWidth(), texture->getHeight());
	physics = new Physics();
}

Player::Player(Scene* s, Vec2 pos)
{
	//printf("creating player \n");
	scene = s;
	currentVelocity = { 0,0 };
	currentPosition = pos;
	texture = new Texture(scene->getRenderer(), textureFile);
	collider = new Collision { scene->getRenderer(), currentPosition.x, currentPosition.y, texture->getWidth(), texture->getHeight() };
	physics = new Physics();
}

Player::~Player()
{
	//printf("destroying player \n");
	delete texture;
	delete collider;
	delete physics;
	texture = nullptr;
	collider = nullptr;
	physics = nullptr;
}

void Player::update(float deltaTime)
{
	checkForFloor();
	checkCollisions(deltaTime);
	move(deltaTime);
}

void Player::draw()
{
	texture->render(currentPosition.x, currentPosition.y);
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
	collider->getBox()->x += currentVelocity.x * deltaTime * groundSpeed;
	collider->getBox()->y += currentVelocity.y * deltaTime;

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

	if (!colliding) {
		currentPosition.x += currentVelocity.x * deltaTime * groundSpeed;
		currentPosition.y += currentVelocity.y * deltaTime;

		if (currentState != GROUNDED) {
			currentVelocity.y += physics->getGravity();
		}
	}

	collider->getBox()->x = currentPosition.x;
	collider->getBox()->y = currentPosition.y;

	// kill player if falls below floor
	if (currentPosition.y > 180) {
		scene->removeEntity(this);
	}
}

void Player::setScene(Scene* s)
{
	scene = s;
}

bool Player::isColliding()
{
	return colliding;
}

bool Player::hasCollider()
{
	return collider != nullptr;
}

Collision* Player::getCollider()
{
	return collider;
}

bool Player::isSolid()
{
	return solid;
}

Vec2 Player::getPosition()
{
	return currentPosition;
}

bool Player::hasPhysics()
{
	return physics != nullptr;
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
			//jumpForce = 400;
			break;
		case NONE:
			texture = new Texture(scene->getRenderer(), "resources/textures/guy.png");
			jumpForce = 200;
			break;
		default:
			scene->removeEntity(this);
			//scene->respawnPlayer();
			break;
	}
}