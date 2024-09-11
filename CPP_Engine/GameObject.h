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
	static const int velocity = 10;

	GameObject();
	GameObject(string name, axes position, Texture* texture);	
	GameObject(const GameObject& src);		
	~GameObject();						

	string getName();
	Texture* getTexture();
	axes getPosition();

	void handleEvent(SDL_Event& e); //  TODO - move to inherited Player class
	void render(int x, int y);
	void move(); // TODO - move to inherited Player class


private:
	string name;
	Texture* texture;
	axes currentPosition; // TODO - move to inherited Player class
	axes currentVelocity; // TODO - move to inherited Player class
};