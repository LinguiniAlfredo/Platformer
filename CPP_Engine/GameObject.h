#pragma once
#include <SDL.h>
#include <string>
#include "Texture.h"

using namespace std;

struct axes {
	int x;
	int y;
};

class GameObject
{
public:
	static const int speed = 400; // TODO - move to inherited Player class
	string name;

	GameObject();
	GameObject(string name, axes position, Texture* texture);	
	GameObject(const GameObject& src);		
	~GameObject();						

	string getName();
	Texture* getTexture();
	axes getPosition();

	void handleEvent(SDL_Event& e, float deltaTime); //  TODO - move to inherited Player class
	void render(int x, int y);
	void move(float deltaTime); // TODO - move to inherited Player class


private:
	Texture* texture;
	axes currentPosition; // TODO - move to inherited Player class
	axes currentVelocity; // TODO - move to inherited Player class

};