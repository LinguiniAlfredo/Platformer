#pragma once
#include <SDL.h>
#include <vector>
class Entity;

class Scene
{
public:
	Scene();
	Scene(SDL_Renderer* renderer);
	Scene(Scene& src);
	~Scene();

	void addEntity(Entity* ent);
	std::vector<Entity*> getEntities(); // TODO - Make a hash map of indexed entities instead
	int getTileSize();
	SDL_Renderer* getRenderer();

private:
	std::vector<Entity*> entities;
	const int TILESIZE = 8;
	SDL_Renderer* renderer;
};

