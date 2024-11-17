#pragma once
#include <string>
#include <vector>
#include "Entity.h"
#include "../Utils/Vec2.h"
class Surface;

class Switch :
	public Entity
{
public:
	Switch(Scene* scene, std::string color, Vec2 currentPosition);
	Switch(Scene* scene, std::string color, Vec2 currentPosition, bool on);
	~Switch();

	void onOff();

private:
	std::string color = "blue";
	std::string onTexture = "resources/textures/switch_blue.png";
	std::string offTexture = "resources/textures/switch_off.png";

	bool on = false;

	void checkCollisions(float deltaTime) override;
};

