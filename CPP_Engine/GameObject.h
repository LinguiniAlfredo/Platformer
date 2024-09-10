#pragma once
#include <SDL.h>
#include <string>
#include "Texture.h"

using namespace std;

struct coordinates {
	int x;
	int y;
};

class GameObject
{
public:
	GameObject();
	GameObject(string name, double width, double height, coordinates position, Texture* texture);	
	GameObject(const GameObject& src);		
	~GameObject();						

	void render(int x, int y);
	//void handleEvent(SDL_Event e);

	double getWidth();				
	double getHeight();
	string getName();
	coordinates getPosition();
	Texture* getTexture();



protected:
	double width;					
	double height;
	string name;
	coordinates position;
	Texture* texture;
};