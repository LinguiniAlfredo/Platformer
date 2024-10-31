#pragma once
#include <SDL.h>
#include <string>
class Vec2;

class Map
{
public:
	Map(std::string filename);
	~Map();

	void load();
    void writeSingleTile(Vec2 tile);

	Uint32* getData();

private:
	Uint32* data;
    std::string filename;
    const int width = 40;
    const int height = 22;
};
