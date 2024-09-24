#pragma once
#include "Entity.h"
class Texture;
class Collision;

class Portal :
	public Entity
{
public:
	Portal();
	~Portal();

	void draw();
	void update(float deltaTime);

	void setScene(Scene* scene);
	void setSolid(bool solid);
	void setTexture(std::string texture);
	void setColliding(bool colliding);
	void setPosition(Vec2 position);
	void setColliderPosition(Vec2 position);
	void setPartner(Portal* partner);

	bool isSolid();
	bool hasCollider();
	bool isColliding();
	
	Vec2 getPosition();
	Scene* getScene();
	Portal* getPartner();
	Collision* getCollider();


private:
	Scene* scene;
	Portal* partner;
	Texture* texture;
	Collision* collider;

	Vec2 position;

	bool colliding;
	bool solid = false;

	void checkCollisions();
	void transportEntity(Entity* ent);
};