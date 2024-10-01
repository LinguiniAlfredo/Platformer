#include "Lift.h"
#include "../Scene.h"
#include "../Components/Collision.h"
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
	for (Vec2 node : path.nodes) {
	
	}
}