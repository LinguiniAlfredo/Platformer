#include "Lift.h"
#include "../Scene.h"
#include "../Components/Collision.h"
#include <cmath>

void Lift::update(float deltaTime)
{
	checkCollisions(deltaTime);
	move(deltaTime);
}

void Lift::move(float deltaTime)
{
	for (Vec2 node : path.nodes) {
	
	}
}