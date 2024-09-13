#pragma once
#include <SDL.h>
#include <string>
#include "Texture.h"
#include "Physics.h"
#include "Collider.h"

using namespace std;

struct axes {
	int x;
	int y;
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

	SDL_Rect* getCollider();
	bool hasCollider();
	bool isColliding();
	void setColliding(bool colliding);

	void handleEvent(SDL_Event& e);
	void render(int x, int y);
	void move(float deltaTime); 

private:
	Texture* texture;
	Physics* physics;
	SDL_Rect* collider;

	state currentState;
	axes currentPosition; 
	axes currentVelocity; 

	bool colliding = false;

};