#include "Entity.h"
#include "Scene.h"
#include "Components/Texture.h"
#include "Components/Collision.h"
#include "Components/Physics.h"

Entity::Entity()
{
	scene = nullptr;
	texture = nullptr;
	collider = nullptr;
	physics = nullptr;
}

Entity::Entity(Scene* scene, std::string textureFile, Vec2 position)
{
	this->scene = scene;
	this->texture = new Texture(scene->getRenderer(), textureFile);
	this->collider = new Collision(scene->getRenderer(), position.x, position.y, texture->getWidth(), texture->getHeight());
	this->physics = new Physics();

	this->currentVelocity = { 0,0 };
	this->currentPosition = position;
}

Entity::Entity(Scene* scene, std::string textureFile, Vec2 position, bool solid)
{
	this->scene = scene;
	this->texture = new Texture(scene->getRenderer(), textureFile);
	this->collider = new Collision(scene->getRenderer(), position.x, position.y, texture->getWidth(), texture->getHeight());
	this->physics = new Physics();

	this->currentVelocity = { 0,0 };
	this->currentPosition = position;

	this->solid = solid;
}

Entity::~Entity()
{
	printf("destroying entity\n");
	if (texture != nullptr) {
		delete texture;
		texture = nullptr;
	}
	if (collider != nullptr) {
		delete collider;
		collider = nullptr;
	}
	if (physics != nullptr) {
		delete physics;
		physics = nullptr;
	}
}

void Entity::draw()
{
	texture->render(currentPosition.x, currentPosition.y);
}

void Entity::update(float deltaTime)
{
	checkCollisions(deltaTime);
}

void Entity::handleEvent(SDL_Event& e)
{
	// implement in inherited classes
}

void Entity::checkCollisions(float deltaTime)
{
	// Check collisions on all other entities
	for (Entity* ent : scene->getEntities()) {
		if (ent->hasCollider() && ent != this) {
			if (SDL_HasIntersection(collider->getBox(), ent->getCollider()->getBox())) {
				colliding = true;
				break;
			}
			else {
				colliding = false;
			}
		}
	}
}

Scene* Entity::getScene()
{
	return scene;
}

Texture* Entity::getTexture()
{
	return texture;
}

Collision* Entity::getCollider()
{
	return collider;
}

Vec2 Entity::getPosition()
{
	return currentPosition;
}

Vec2 Entity::getVelocity()
{
	return currentVelocity;
}

bool Entity::isColliding()
{
	return colliding;
}

bool Entity::isSolid()
{
	return solid;
}

void Entity::setScene(Scene* scene)
{
	this->scene = scene;
}

void Entity::setTexture(std::string path)
{
	if (texture != nullptr) {
		delete texture;
		texture = nullptr;
	}
	texture = new Texture(scene->getRenderer(), path);
}

void Entity::setSolid(bool solid)
{
	this->solid = solid;
}

void Entity::setPosition(int x, int y)
{
	this->currentPosition.x = x;
	this->currentPosition.y = y;
}

void Entity::setColliderPosition(int x, int y)
{
	this->collider->getBox()->x = x;
	this->collider->getBox()->y = y;
}

void Entity::setColliding(bool colliding)
{
	this->colliding = colliding;
}

bool Entity::hasCollider()
{
	return collider != nullptr;
}

bool Entity::hasPhysics()
{
	return physics != nullptr;
}