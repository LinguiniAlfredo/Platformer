#pragma once
#include <SDL.h>
#include <string>
#include "Texture.h"
#include "Physics.h"
#include "Collision.h"

using namespace std;

struct axes {
	float x;
	float y;
};

enum state {
	GROUNDED,
	AIRBORNE
};

// TODO - Move physics, collision and movement to Player class

class GameObject
{
public:
	static const int speed = 400; 
	string name;

	GameObject();
	GameObject(string name, axes position, Texture* texture);	
	GameObject(string name, axes position, Texture* texture, bool hasPhysics);	
	GameObject(string name, axes position, Texture* texture, bool hasPhysics, bool hasCollision);	
	GameObject(const GameObject& src);		
	~GameObject();						

	string getName();
	axes getPosition();

	Texture* getTexture();

	Physics* getPhysics();
	bool hasPhysics();

	Collision* getCollider();
	bool hasCollider();

	void handleEvent(SDL_Event& e, float deltaTime);
	void render(float x, float y);
	void move(float deltaTime); 

private:
	Texture* texture;
	Physics* physics;
	Collision* collider;

	state currentState;
	axes currentPosition; 
	axes currentVelocity; 

};