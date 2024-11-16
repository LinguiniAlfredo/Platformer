#pragma once
#include <algorithm>
#include "stdio.h"
#include "Scene.h"
#include "Editor/Map.h"
#include "Entities/Entity.h"
#include "Entities/Surface.h"
#include "Entities/Player.h"

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

    loadMap();
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
    delete map;
    map = nullptr;
    
	delete camera;
	camera = nullptr;

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

void Scene::clearEntities()
{
    for (Entity* ent : entities) {
        removeEntity(ent);
    }
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
    //clearEntities();
    std::vector<int> tiles = map->getData();
    for (int i = 0; i < tiles.size(); i++) {
           int y = static_cast<int>(i / 40);
           int x = static_cast<int>(i - (y * 40)); 

           tileToEntity(tiles.at(i), x, y);
    }
}

// maybe move this to Editor, will also have TileType enum available
void Scene::tileToEntity(int tile, int x, int y)
{
    switch(tile) {
        case 0:
            break;
        case 1:
           addEntity(new Surface(this, "resources/textures/ground_tile.png", { x, y }));
           break;
        case 9:
           addEntity(new Player(this, "resources/textures/guy.png", { x, y }));
           break;
        default:
           break;
    }
}

