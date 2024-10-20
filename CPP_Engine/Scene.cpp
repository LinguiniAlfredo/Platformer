#pragma once
#include "Scene.h"
#include "Entities/Entity.h"
#include <algorithm>
#include <iostream>

Scene::Scene() 
{
	renderer = nullptr;
	camera = nullptr;
}

Scene::Scene(SDL_Renderer* r) 
{
	renderer = r;
	camera = nullptr;
}

Scene::Scene(SDL_Renderer* r, SDL_Rect* c)
{
	renderer = r;
	camera = c;
}

Scene::Scene(Scene& src)
{
	renderer = src.renderer;
	for (Entity* ent : src.getEntities()) {
		entities.push_back(ent);
	}
}

Scene::~Scene()
{
	//printf("destroying scene\n");
	for (Entity* ent : entities) {
		delete ent;
		ent = nullptr;
	}
	entities.clear();

	for (Entity* ent : trashBin) {
		delete ent;
		ent = nullptr;
	}
	trashBin.clear();

	delete camera;
	camera = nullptr;
}

void Scene::addEntity(Entity* ent)
{
	ent->setScene(this);
	entities.push_back(ent);
}

void Scene::removeEntity(Entity* ent)
{
	binIt(ent);
	entities.erase(std::remove(entities.begin(), entities.end(), ent), entities.end());
}

void Scene::binIt(Entity* ent)
{
	trashBin.push_back(ent);
}

void Scene::clearTrash()
{
	for (Entity* ent : trashBin) {
		delete ent;
		ent = nullptr;
	}

	trashBin.clear();
}

std::vector<Entity*> Scene::getEntities()
{
	return entities;
}

int Scene::getTileSize()
{
	return TILESIZE;
}

SDL_Renderer* Scene::getRenderer()
{
	return renderer;
}

Entity* Scene::getPlayer()
{
	//auto it = std::find_if(entities.begin(), entities.end(), 
	//	[] (Entity* ent) {
	//		return ent->name == "player";
	//	});
	//int index = std::distance(entities.begin(), it);
	return entities.at(1);
}

SDL_Rect* Scene::getCamera()
{
	return camera;
}

