#include "Scene.h"
#include <algorithm>

Scene::Scene()
{

}

Scene::Scene(Scene &src)
{
	for (GameObject* obj : src.getGameObjects())
	{
		gameObjects.push_back(obj);
	}
}

Scene::~Scene()
{
	for (GameObject* obj : gameObjects)
	{
		delete obj;
		obj = nullptr;
	}
	gameObjects.clear();

}

void Scene::addGameObject(GameObject* obj)
{
	gameObjects.push_back(obj);
}

vector<GameObject*> Scene::getGameObjects()
{
	return gameObjects;
}

GameObject* Scene::getGameObject(string name)
{
	return gameObjects.at(2);
}

void Scene::detectCollisions()
{
	for (int i = 0; i < getGameObjects().size(); i++)
	{
		GameObject* current = getGameObjects().at(i);
		for (int j = 0; j < getGameObjects().size(); j++)
		{
			if (j != i)
			{
				GameObject* next = getGameObjects().at(j);
				if (SDL_HasIntersection(current->getCollider(), next->getCollider()))
				{
					current->setColliding(true);
					break;
				}
				else
				{
					current->setColliding(false);
				}
			}
			
		}

	}
}
