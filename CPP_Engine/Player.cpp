#pragma once
#include <iostream>
#include "Player.h"
#include "Texture.h"
#include "Scene.h"
#include "Physics.h"

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

	checkCollisions(deltaTime); // moves colliders, checks intersects
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
		if (key == SDLK_SPACE)
		{
			if (currentState == GROUNDED)
			{
				currentVelocity.y = -1;
				currentState = JUMPING;
			}
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
			currentVelocity.y = 1;
			currentState = FALLING;
		}
	}
}

void Player::checkCollisions(float deltaTime)
{
	float xMovement = 0, yMovement = 0;
    xMovement = currentVelocity.x * deltaTime * groundSpeed;

	if (currentState == JUMPING)
	{
		// calculate acceleration up to jumpHeight
		// once reaches jumpHeight, set FALLING
		yMovement = currentVelocity.y * deltaTime * jumpForce;
	} 
	else if (currentState == FALLING)
	{
		currentVelocity.y = 1;
		yMovement = currentVelocity.y * deltaTime * jumpForce;
	}

	collider->x += xMovement;
	collider->y += yMovement;

	// Check collisions on all other entities
	for (Entity* ent : scene->getEntities())
	{
		if (ent->hasCollider() && ent != this)
		{
			if (SDL_HasIntersection(collider, ent->getCollider()))
			{
				colliding = true;
				if (ent->getPosition().y > currentPosition.y + texture->getHeight() / 2)
					currentState = GROUNDED;
				else
					currentState = FALLING;
				break;
			}
			else
			{
				colliding = false;
			}
		}
	}
}

void Player::move(float deltaTime)
{
	// TODO - put code that is the same in checkCollisions and this one 
	//		  into a separate function

	float xMovement = 0, yMovement = 0;
	xMovement = currentVelocity.x * deltaTime * groundSpeed;

	if (currentState == JUMPING)
	{
		// calculate acceleration up to jumpHeight
		// once reaches jumpHeight, set FALLING
		yMovement = currentVelocity.y * deltaTime * jumpForce;
	}
	else if (currentState == FALLING)
	{
		currentVelocity.y = 1;
		yMovement = currentVelocity.y * deltaTime * jumpForce;
	}

	if (!colliding)
	{
		currentPosition.x += xMovement;
		currentPosition.y += yMovement;

		if (currentPosition.y < 180 - jumpHeight)
			currentState = FALLING;
	}
	else if (colliding && yMovement > 0) 
	{
		currentPosition.x += xMovement;
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