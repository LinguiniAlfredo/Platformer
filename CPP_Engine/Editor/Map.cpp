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
    std::string tile;
    std::ifstream file(filename);

	while (getline(file, tile, ',')) {
        if (file.eof()) {
            break;
        }
        data.push_back(stoi(tile));
    }
    file.close();
}

void Map::writeSingleTile(Vec2 pos, int tileType)
{
    int index = pos.y * 40 + pos.x;
    data.at(index) = tileType;
}


std::vector<int> Map::getData()
{
	return data;
}
