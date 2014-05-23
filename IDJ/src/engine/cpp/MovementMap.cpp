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

/**
 * Builds the movement map. The movement map consists of a
 * two-dimensional integer matrix, with values that can be 0 or 1,
 * 1 for the spaces on the map that cannot be walked into, 0 for the rest.
 */
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
    mapFile >> this->mapWidth; mapFile >> a;
    mapFile >> this->mapHeight; mapFile >> a;
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

    for (i = 0; i < (int)movementMatrix.size(); i++)
        if (movementMatrix[i] == -1)
        {
            std::cout << "Error! The movement map was not built correctly." << std::endl;
            break;
        }
}

int& MovementMap::At(int x, int y)
{
    return movementMatrix[x + mapWidth * y];
}

/**
 * Returns true if the point given is in
 * Returns the index of the tile corresponding to a given pixel position.
 * If the given point is outside the limits of the map, returns -2.
 * (-1 means that there is no tile).
 */
bool MovementMap::IsZero(int x, int y)
{
    if (x < 0 || x > mapWidth*tileWidth) return -2;
    if (y < 0 || y > mapHeight*tileHeight) return -2;
    int x_index=0, y_index=0;
    for (int i = 1; x >= tileWidth*i; i++)
        x_index++;
    for (int i = 1; y >= tileHeight*i; i++)
        y_index++;
    return At(x_index, y_index) == 0 ? true : false;
}
