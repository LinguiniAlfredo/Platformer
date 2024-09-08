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

private:
	vector<GameObject*> gameObjects;
};

