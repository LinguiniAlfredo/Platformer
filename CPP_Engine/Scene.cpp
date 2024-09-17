#pragma once
#include "Scene.h"
#include "Entities/Entity.h"
#include <algorithm>
#include <iostream>

Scene::Scene() 
{
	renderer = nullptr;
}

Scene::Scene(SDL_Renderer* r) 
{
	renderer = r;
}

Scene::Scene(Scene& src)
{
	renderer = src.renderer;
	for (Entity* ent : src.getEntities())
	{
		entities.push_back(ent);
	}
}

Scene::~Scene()
{
	printf("destroying scene\n");
	for (Entity* ent : entities)
	{
		delete ent;
		ent = nullptr;
	}
	entities.clear();
}

void Scene::addEntity(Entity* ent)
{
	ent->setScene(this);
	entities.push_back(ent);
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

