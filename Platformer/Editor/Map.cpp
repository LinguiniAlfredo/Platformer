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

std::vector<int> Map::getData()
{
	return data;
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

void Map::write()
{
    std::string tile;
    std::ofstream file(filename);

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            file << data.at((y * width) + x);
            file << ',';
        }
        file << "\n";
    }

    file.close();
}

void Map::addTile(Vec2 pos, int tileType)
{
    int index = pos.y * width + pos.x;
    if (data.at(index) != tileType) {
        data.at(index) = tileType;
    }
}

void Map::removeTile(Vec2 pos)
{
    int index = pos.y * width + pos.x;
    if (data.at(index) != 0) {
        data.at(index) = 0;
    }
}



