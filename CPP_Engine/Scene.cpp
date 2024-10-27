#pragma once
#include "Scene.h"
#include "Entities/Entity.h"
#include "Editor/Map.h"
#include <algorithm>
#include <iostream>

Scene::Scene() 
{
	renderer = nullptr;
	camera = nullptr;
	map = nullptr;
}

Scene::Scene(SDL_Renderer* r) 
{
	renderer = r;
	camera = nullptr;
	map = nullptr;
}

Scene::Scene(SDL_Renderer* r, SDL_Rect* c)
{
	renderer = r;
	camera = c;
	map = nullptr;
}

Scene::Scene(SDL_Renderer* r, SDL_Rect* c, Map* m)
{
	renderer = r;
	camera = c;
	map = m;
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

Map* Scene::getMap()
{
	return map;
}

void Scene::loadMap()
{
   // for (int i = 0; i < map.size(); i++) {
        // if value = 1 
        //      addEntity(new Player(this, "guy.png", {x,y})
        // else if value = 2
        //      addEntity(new Surface(this, "groundtile.png", {x,y})
        //
    // }
}
