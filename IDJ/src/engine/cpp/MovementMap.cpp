/*
 * MovementMap.cpp
 *
 *  Created on: May 22, 2014
 *      Author: Gabriel Naves
 */

#include "../include/MovementMap.h"

MovementMap::MovementMap(std::string file, const TileSet& tileSet, int layer)
{
    tileWidth = tileSet.GetTileWidth();
    tileHeight = tileSet.GetTileHeight();

    BuildMovementMap(file, layer);
}

void MovementMap::BuildMovementMap(std::string file, int layer)
{
    std::ifstream mapFile;
    mapFile.open(file);
    if (!mapFile.is_open())
    {
        std::cerr << "Could not open tileMap file." << std::endl;
        return;
    }

    std::string str;
    char a;
    int mapDepth;
    mapFile >> this->mapWidth;
    mapFile >> a;
    mapFile >> this->mapHeight;
    mapFile >> a;
    mapFile >> mapDepth;
    getline(mapFile, str);
    getline(mapFile, str);

    if (layer >= mapDepth || layer < 0)
        { std::cerr << "ERROR: Invalid layer!" << std::endl; return; }

    int i = 0, j = 0, k = 0;
    std::string num;
    num.resize(2);
    movementMatrix.resize(mapWidth*mapHeight);
    for (int i = 0; i < (int)movementMatrix.size(); i++) movementMatrix[i] = -1;

    while (k < layer)
    {
        for (j = 0; j < mapHeight; j++)
        {
            getline(mapFile, str);
        }
        getline(mapFile, str);
        k++;
    }

    j = 0;
    while (getline(mapFile, str))
    {
        if (str.size() == 0) break;
        while (str.size() > 1)
        {
            num[0] = str[0], num[1] = str[1];
            str.erase(0, 3);
            if (std::stoi(num) == 0)
                At(i, j) = 0;
            else
                At(i,j) = 1;
            ++i;
        }
        i = 0;
        ++j;
    }
}

int& MovementMap::At(int x, int y)
{
    return movementMatrix[x + mapWidth * y];
}
