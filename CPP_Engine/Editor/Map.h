#pragma once
#include <SDL.h>
#include <string>

class Map
{
public:
	Map(std::string file);
	~Map();

	void load(std::string file);

	Uint32* getData();

private:
	Uint32* data;

    const int width = 40;
    const int height = 22;
};
