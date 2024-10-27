#pragma once
#include <SDL.h>
#include <vector>
class Entity;
class Player;
class Map;

class Scene
{
public:
	Scene();
	Scene(SDL_Renderer* renderer); // do i need this?
	Scene(SDL_Renderer* renderer, SDL_Rect* camera); // do i need this?
	Scene(SDL_Renderer* renderer, SDL_Rect* camera, Map* map);
	Scene(Scene& src);
	~Scene();

	void addEntity(Entity* ent);
	void removeEntity(Entity* ent);
	void binIt(Entity* ent);
	void clearTrash();

	std::vector<Entity*> getEntities();
	int getTileSize();
	SDL_Renderer* getRenderer();
	Entity* getPlayer();
	SDL_Rect* getCamera();

	Map* getMap();
    void loadMap();

private:
	std::vector<Entity*> entities;
	std::vector<Entity*> trashBin;

	SDL_Renderer* renderer;
	SDL_Rect* camera;
	Map* map;

	const int TILESIZE = 8;
};

