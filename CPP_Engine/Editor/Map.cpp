#include "Map.h"
#include <iostream>
#include <fstream>
#include "Utils/Vec2.h"

Map::Map(std::string filename)
{
    this->filename = filename;
	load();
}

Map::~Map()
{

}

void Map::load()
{
	std::string line;
	std::ifstream input(filename);
	if (input.is_open()) {
		for (int y = 0; y < height; y++) {
            int c = getchar();
            for (int x = 0; c != '\n'; x++) {
                if (c == ',') {
                    continue;
                } else {
                    //fill data with value
                }
            }
		}


		input.close();
	}
}

void Map::writeSingleTile(Vec2 pos)
{

}


Uint32* Map::getData()
{
	return data;
}
