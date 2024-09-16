#pragma once
#include <iostream>
#include "Player.h"
#include "Texture.h"
#include "Scene.h"
#include "Physics.h"
#include <cmath>

Player::Player(SDL_Renderer* renderer)
{
	printf("creating player \n");
	currentVelocity = { 0,0 };
	currentPosition = { 0,0 };
	texture = new Texture(renderer, textureFile);
	collider = new SDL_Rect { currentPosition.x, currentPosition.y, texture->getWidth(), texture->getHeight() };
	physics = new Physics();
}

Player::Player(SDL_Renderer* renderer, vec2 pos)
{
	printf("creating player \n");
	currentVelocity = { 0,0 };
	currentPosition = pos;
	texture = new Texture(renderer, textureFile);
	collider = new SDL_Rect{ currentPosition.x, currentPosition.y, texture->getWidth(), texture->getHeight() };
	physics = new Physics();
}

Player::~Player()
{
	printf("destroying player \n");
	delete texture;
	delete collider;
	delete physics;
	texture = nullptr;
	collider = nullptr;
	physics = nullptr;
}

void Player::update(float deltaTime)
{
	// check floor collisions, set grounded/airborne state
	// check other collisions
	// move character based on input and collisions

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
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{
		SDL_Keycode key = e.key.keysym.sym;
		if (key == SDLK_a)
		{
			currentVelocity.x = -1;
		}
		if (key == SDLK_d)
		{
			currentVelocity.x = 1;
		}
		if (key == SDLK_SPACE && currentState == GROUNDED)
		{
			currentVelocity.y = -1 * jumpForce;
			currentState = AIRBORNE;
		}

	}
	if (e.type == SDL_KEYUP && e.key.repeat == 0)
	{
		SDL_Keycode key = e.key.keysym.sym;
		if (key == SDLK_a)
		{
			if (currentVelocity.x < 0)
				currentVelocity.x = 0;
		}
		if (key == SDLK_d)
		{
			if (currentVelocity.x > 0)
				currentVelocity.x = 0;
		}
		if (key == SDLK_SPACE)
		{
			//currentState = AIRBORNE;
		}
	}
}

void Player::checkForFloor()
{
	if (currentState == GROUNDED)
	{
		for (Entity* ent : scene->getEntities())
		{
			if (ent->getPosition().y - currentPosition.y == scene->getTileSize() &&
				currentPosition.x + collider->w >= ent->getPosition().x && currentPosition.x < ent->getPosition().x + ent->getCollider()->w)
			{
				return;
			}

		}
		currentState = AIRBORNE; // if nothing underneath player, set AIRBORNE
	}
}

void Player::checkCollisions(float deltaTime)
{
	// move collider where player will be next frame and check collisions.
	collider->x += currentVelocity.x * deltaTime * groundSpeed;
	collider->y += currentVelocity.y * deltaTime;

	if (currentState != GROUNDED)
		currentVelocity.y += physics->getGravity();

	for (Entity* ent : scene->getEntities())
	{
		if (ent->hasCollider() && ent != this)
		{
			if (SDL_HasIntersection(collider, ent->getCollider()))
			{
				colliding = true;
				resolveCollision(ent);

				if (ent->getPosition().y > currentPosition.y)
				{
					currentState = GROUNDED;
				}
				break;
			}
			else
			{
				colliding = false;
			}
		}
	}
}

void Player::resolveCollision(Entity* ent)
{
	// if collision is on the right of player and x velocity is positive
	if (currentVelocity.x > 0 && ent->getPosition().x > currentPosition.x)
	{
		currentPosition.x = ent->getPosition().x - scene->getTileSize();
		currentVelocity.x = 0;
	}
	// if collision is on left of player and x velocity is negative
	if (currentVelocity.x < 0 && ent->getPosition().x < currentPosition.x)
	{
		currentPosition.x = ent->getPosition().x + scene->getTileSize();
		currentVelocity.x = 0;
	}
	// if collision below player and y velocity is positive
	if (currentVelocity.y > 0 && ent->getPosition().y > currentPosition.y)
	{
		currentPosition.y = ent->getPosition().y - scene->getTileSize();
		currentVelocity.y = 0;
	}
	// if collision above player and y velocity is negative
	if (currentVelocity.y < 0 && ent->getPosition().y < currentPosition.y)
	{
		currentPosition.y = ent->getPosition().y + scene->getTileSize();
		currentVelocity.y = 1;
	}
}

void Player::move(float deltaTime)
{
	// TODO - put state changes in a function ?

	// Position += Velocity
	// Velocity += Acceleration

	if (!colliding)
	{
		currentPosition.x += currentVelocity.x * deltaTime * groundSpeed;
		currentPosition.y += currentVelocity.y * deltaTime;

		if (currentState != GROUNDED)
			currentVelocity.y += physics->getGravity();
	}

	collider->x = currentPosition.x;
	collider->y = currentPosition.y;
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

SDL_Rect* Player::getCollider()
{
	return collider;
}

vec2 Player::getPosition()
{
	return currentPosition;
}