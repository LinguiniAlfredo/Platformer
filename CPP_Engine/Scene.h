#pragma once
#include <vector>
#include "GameObject.h"

class Scene
{
public:
	Scene();
	Scene(Scene &src);
	~Scene();

	void addGameObject(GameObject* obj);
	vector<GameObject*> getGameObjects();

	GameObject* getGameObject(string name);

private:
	vector<GameObject*> gameObjects;
};

