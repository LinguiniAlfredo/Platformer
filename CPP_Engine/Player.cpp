#pragma once
#include <iostream>
#include "Player.h"
#include "Texture.h"
#include "Scene.h"

using namespace std;

Player::Player(SDL_Renderer* renderer)
{
	cout << "creating player \n";
	currentVelocity = { 0,0 };
	currentPosition = { 0,0 };
	texture = new Texture(renderer, textureFile, 60, 60);
	collider = new SDL_Rect { currentPosition.x, currentPosition.y, texture->getWidth(), texture->getHeight() };
}

Player::~Player()
{
	cout << "destroying player \n";
	delete texture;
	delete collider;
	texture = nullptr;
	collider = nullptr;
}

void Player::update(float deltaTime)
{
	checkCollisions(deltaTime); // moves colliders, checks intersects
	setState(); // sets GROUNDED/AIRBORNE based on collisions
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
		if (key == SDLK_w)
		{
			currentVelocity.y = -1;
		}
		if (key == SDLK_s)
		{
			currentVelocity.y = 1;
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
		if (key == SDLK_w)
		{
			if (currentVelocity.y < 0)
				currentVelocity.y = 0;
		}
		if (key == SDLK_s)
		{
			if (currentVelocity.y > 0)
				currentVelocity.y = 0;
		}
	}
}

void Player::checkCollisions(float deltaTime)
{
	// Move collider
	float xMovement = currentVelocity.x * deltaTime * speed;
	float yMovement = currentVelocity.y * deltaTime * speed;

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
				break;
			}
			else
			{
				colliding = false;
			}
		}
	}
}

void Player::setState()
{
	// if colliding with floor, set GROUNDED, otherwise AIRBORNE
}

void Player::move(float deltaTime)
{
	float xMovement = currentVelocity.x * deltaTime * speed;
	float yMovement = currentVelocity.y * deltaTime * speed;

	if (!colliding)
	{
		currentPosition.x += xMovement;
		currentPosition.y += yMovement;
	}
	collider->y = currentPosition.y;
	collider->x = currentPosition.x;
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