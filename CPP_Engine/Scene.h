#pragma once
#include <vector>
class Entity;

class Scene
{
public:
	Scene();
	Scene(Scene& src);
	~Scene();

	void addEntity(Entity* ent);
	std::vector<Entity*> getEntities();

private:
	std::vector<Entity*> entities;
};

