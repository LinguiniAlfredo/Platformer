#include "Portal.h"
#include "Scene.h"
#include "Components/Collision.h"
#include "Components/Texture.h"

Portal::Portal()
{

}

Portal::~Portal() 
{

}

void Portal::draw()
{
	texture->render(position.x, position.y);
}

void Portal::update(float deltaTime)
{
	checkCollisions();
}

void Portal::checkCollisions()
{
	// Check collisions on all other entities
	for (Entity* ent : scene->getEntities()) {
		if (ent->hasCollider() && ent != this) {
			if (SDL_HasIntersection(collider->getBox(), ent->getCollider()->getBox())) {
				colliding = true;
				transportEntity(ent);
				break;
			}
			else {
				colliding = false;
			}
		}
	}
}

void Portal::transportEntity(Entity* ent)
{

}

void Portal::setScene(Scene* scene)
{
	this->scene = scene;
}

void Portal::setSolid(bool solid)
{
	this->solid = solid;
}

void Portal::setTexture(std::string path)
{
	if (texture != nullptr) {
		delete texture;
		texture = nullptr;
	}
	texture = new Texture(scene->getRenderer(), path);
}

void Portal::setColliding(bool colliding)
{
	this->colliding = colliding;
}

void Portal::setPosition(Vec2 position)
{
	this->position = position;
}

void Portal::setColliderPosition(Vec2 position)
{
	this->collider->getBox()->x = position.x;
	this->collider->getBox()->y = position.y;
}

void Portal::setPartner(Portal* partner)
{
	this->partner = partner;
}

Scene* Portal::getScene()
{
	return scene;
}

Collision* Portal::getCollider()
{
	return collider;
}

bool Portal::isColliding()
{
	return colliding;
}

bool Portal::hasCollider()
{
	return collider != nullptr;
}

bool Portal::isSolid()
{
	return solid;
}

Vec2 Portal::getPosition()
{
	return position;
}

Portal* Portal::getPartner()
{
	return partner;
}