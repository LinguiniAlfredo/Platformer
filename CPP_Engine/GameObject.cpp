#include <iostream>
#include "GameObject.h"
using namespace std;

GameObject::GameObject()
{
	name = "";
	position = { 0,0 };
	texture = nullptr;
}

GameObject::GameObject(string n, coordinates p, Texture* t)
{
	cout << "creating gobj " << n << "\n";
	name = n;
	texture = t;
	position = p;
}

GameObject::GameObject(const GameObject& src)
{
	name = src.name;
	texture = src.texture;
	position = src.position;
}

GameObject::~GameObject()
{
	cout << "destroying gobj " << name << "\n";
	delete texture;
	texture = nullptr;
}

void GameObject::render(int x, int y)
{
	texture->render(x, y);
}

string GameObject::getName()
{
	return name;
}

coordinates GameObject::getPosition()
{
	return position;
}

Texture* GameObject::getTexture()
{
	return texture;
}
