#pragma once
#include <algorithm>
#include "stdio.h"
#include "Scene.h"
#include "Editor/Map.h"
#include "Editor/Editor.h"
#include "Editor/Pallete.h"
#include "Entities/Entity.h"
#include "Entities/Surface.h"
#include "Entities/Player.h"
#include "Entities/Pickup.h"
#include "Entities/Switch.h"
#include "Entities/Box.h"

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
	return entities.at(0);
}

SDL_Rect* Scene::getCamera()
{
	return camera;
}

Map* Scene::getMap()
{
	return map;
}

// loads entire map
void Scene::loadMap()
{
    std::vector<int> tiles = map->getData();
    for (int i = 0; i < tiles.size(); i++) {
           int y = static_cast<int>(i / map->width);
           int x = static_cast<int>(i - (y * map->width)); 

           tileDataToEntity(tiles.at(i), x, y);
    }
}

// only loads a single target tile
void Scene::loadMap(Vec2 targetTile)
{
    std::vector<int> tiles = map->getData();

    int index = (targetTile.y * map->width) + targetTile.x;
    tileDataToEntity(tiles.at(index), targetTile.x, targetTile.y);
}

void Scene::tileDataToEntity(int tile, int x, int y)
{
    switch(tile) {
        case BLANK:
        {
            Entity* ent = getEntityAtLocation({ x, y });
            if (ent != nullptr) {
                removeEntity(ent);
            }
        } break;

        case GUY:
           addEntity(new Player(this, "resources/textures/guy.png", { x, y }));
           break;

        case GROUND:
           addEntity(new Surface(this, "resources/textures/ground_tile.png", { x, y }));
           break;
           
        case GRASS:
            addEntity(new Surface(this, "resources/textures/grass_1.png", { x, y }, false));
            break;

        case COIN:
            addEntity(new Pickup(this, "coin", { x, y }, true));
            break;

        case FLOWER:
            addEntity(new Pickup(this, "flower", { x, y }, true));
            break;

        case SWBLOCK_RED:
            addEntity(new Surface(this, "resources/textures/trans_block_red.png", { x, y }, false));
            break;
        
        case SWBLOCK_GREEN:
            addEntity(new Surface(this, "resources/textures/trans_block_green.png", { x, y }, false));
            break;

        case SWBLOCK_BLUE:
            addEntity(new Surface(this, "resources/textures/trans_block_blue.png", { x, y }, false));
            break;
        
        case SWITCH_RED:
            addEntity(new Switch(this, "red", { x, y }));
            break;

        case SWITCH_GREEN:
            addEntity(new Switch(this, "green", { x, y }));
            break;

        case SWITCH_BLUE:
            addEntity(new Switch(this, "blue", { x, y }));
            break;

        case SIGN:
            addEntity(new Surface(this, "resources/textures/sign.png", { x, y }, false));
            break;

        case BOX:
        {
            Pickup* flower = new Pickup(this, "flower", { x, y }, false);
            addEntity(new Box(this, flower, { x, y }));
        } break;

        default:
           break;
    }
}

Entity* Scene::getEntityAtLocation(Vec2 location)
{
    for (Entity* ent : entities) {
        if (ent->getPosition() == location) {
            return ent;
        }
    }
    return nullptr;
}

