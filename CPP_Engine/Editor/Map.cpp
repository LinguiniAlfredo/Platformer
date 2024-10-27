#include "Map.h"
#include <iostream>
#include <fstream>

Map::Map(std::string file)
{
	load(file);
}

Map::~Map()
{

}

void Map::load(std::string file)
{
	std::string line;
	std::ifstream input(file);
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

Uint32* Map::getData()
{
	return data;
}
