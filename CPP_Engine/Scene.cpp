#include "Scene.h"

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

