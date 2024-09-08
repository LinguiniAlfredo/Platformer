#include <SDL.h>
#include <string>
#pragma once
using namespace std;

struct coordinates {
	int x;
	int y;
};

class GameObject
{
public:
	GameObject();
	GameObject(string name, double width, double height, coordinates position, SDL_Texture* texture);	
	GameObject(const GameObject& src);		
	~GameObject();						

	double getWidth();				
	double getHeight();
	string getName();
	coordinates getPosition();
	SDL_Texture* getTexture();
	SDL_Rect* getSize();


private:
	double width;					
	double height;
	string name;
	coordinates position;
	SDL_Texture* texture;
	SDL_Rect* scaledSize;
};