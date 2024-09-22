#include "Lift.h"
#include "Scene.h"
#include "Components/Collision.h"
#include <cmath>

void Lift::update(float deltaTime)
{
	checkCollisions(deltaTime);
	move(deltaTime);
}

void Lift::checkCollisions(float deltaTime)
{
	// Check collisions on all other entities
	for (Entity* ent : getScene()->getEntities()) {
		if (ent->hasCollider() && ent != this) {
			if (SDL_HasIntersection(getCollider()->getBox(), ent->getCollider()->getBox())) {
				setColliding(true);
				break;
			}
			else {
				setColliding(false);
			}
		}
	}
}

void Lift::move(float deltaTime)
{
	//float deltaY = range * sin(deltaTime);
	//currentVelocity.y = deltaY * speed;
	//setPosition({ getPosition().x, getPosition().y + getVelocity().y});
	//setColliderPosition(getPosition());
	//frameCount++;
}

Vec2 Lift::getVelocity()
{
	return currentVelocity;
}

void Lift::setVelocity(Vec2 velocity)
{
	this->currentVelocity = velocity;
}