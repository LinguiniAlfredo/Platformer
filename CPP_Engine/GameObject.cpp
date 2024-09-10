#include <iostream>
#include "GameObject.h"
using namespace std;

GameObject::GameObject()
{
	name = "";
	width = 0;
	height = 0;
	position = { 0,0 };
}

GameObject::GameObject(string n, double w, double h, coordinates p, Texture t)
{
	cout << "creating gobj " << n << "\n";
	name = n;
	width = w;
	height = h;
	texture = t;
	position = p;
}

GameObject::GameObject(const GameObject& src)
{
	name = src.name;
	width = src.width;
	height = src.height;
	texture = src.texture;
	position = src.position;
}

GameObject::~GameObject()
{
	cout << "destroying gobj " << name << "\n";
	texture.free();
}

double GameObject::getWidth()
{
	return width;
}

double GameObject::getHeight()
{
	return height;
}

string GameObject::getName()
{
	return name;
}

coordinates GameObject::getPosition()
{
	return position;
}

Texture GameObject::getTexture()
{
	return texture;
}
