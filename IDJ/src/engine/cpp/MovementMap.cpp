/*
 * MovementMap.cpp
 *
 *  Created on: May 22, 2014
 *      Author: Gabriel Naves
 */

#include "../include/MovementMap.h"

MovementMap::MovementMap(std::string file, const TileSet& tileSet)
{
    tileWidth = tileSet.GetTileWidth();
    tileHeight = tileSet.GetTileHeight();
    currentLayer = 0;

    BuildMovementMap(file);
}

/**
 * Builds the movement map. The movement map consists of a
 * two-dimensional integer matrix, with values that can be 0 or 1,
 * 1 for the spaces on the map that cannot be walked into, 0 for the rest.
 */
void MovementMap::BuildMovementMap(std::string file)
{
    std::ifstream mapFile;
    mapFile.open(file);

    if (!mapFile.is_open())
    {
        std::cerr << "Could not open movementMap file." << std::endl;
        return;
    }

    std::string str;
    char a;
    mapFile >> this->mapWidth;
    mapFile >> a;
    mapFile >> this->mapHeight;
    mapFile >> a;
    mapFile >> this->mapDepth;
    getline(mapFile, str);
    getline(mapFile, str);

    int i = 0, j = 0, k = 0;
    std::string num;
    num.resize(2);
    movementMatrix.resize(mapWidth*mapHeight*mapDepth);
    for (unsigned int i = 0; i < movementMatrix.size(); i++) movementMatrix[i] = -1;

    while (getline(mapFile, str))
    {
        if (str.size() == 0)
        {
            ++k;
            i = j = 0;
            getline(mapFile, str);
        }
        while (str.size() > 1)
        {
            num[0] = str[0], num[1] = str[1];
            str.erase(0, 3);
            if (std::stoi(num) == 0) At(i, j, k) = 0;
            else At(i, j, k) = 1;
            ++i;
        }
        i = 0;
        ++j;
    }
}

int& MovementMap::At(int x, int y, int z)
{
    if (z == -1) z = currentLayer;
    return movementMatrix[x + mapWidth * y + mapWidth * mapHeight * z];
}

/**
 * Returns true if the value of the tile corresponding to
 * a given pixel position is 0, false if the value of the tile is 1.
 * If the given point is outside the limits of the map, returns false.
 */
bool MovementMap::IsZero(int x, int y, int z)
{
    if (z == -1) z = currentLayer;
    if (x < 0 || x > mapWidth*tileWidth) return false;
    if (y < 0 || y > mapHeight*tileHeight) return false;
    int x_index=0, y_index=0;
    for (int i = 1; x >= tileWidth*i; i++)
        x_index++;
    for (int i = 1; y >= tileHeight*i; i++)
        y_index++;
    return At(x_index, y_index, z) == 0 ? true : false;
}

/**
 * Finds the shortest absolute distance between a given position
 * and the nearest valid tile, relative to the x axis. Valid tiles
 * are 0 on the movementMatrix,and invalid ones are 1.
 * The distance will be negative if the closest valid tile is to the left
 * of the position, and positive if to the right.
 */
float MovementMap::FindXDistance(float xPos, float yPos)
{
    if (IsZero(xPos, yPos)) return 0;
    if ((yPos < 0 || yPos > mapHeight*tileHeight)) return 0;
    float leftDistance = -999999, rightDistance = 999999;
    float x = xPos;
    // Checks for closest position to the left
    while (x > 0)
    {
        x = x - tileWidth;
        if (IsZero(x, yPos))
        {
            int xIndex = 0;
            for (int i = 1; x >= tileWidth*i; i++)
                xIndex++;
            leftDistance = tileWidth*(xIndex+1) - xPos;
            break;
        }
    }
    x = xPos;
    // Checks for closest position to the right
    while (x < mapWidth * tileWidth)
    {
        x = x + tileWidth;
        if (IsZero(x, yPos))
        {
            int xIndex = 0;
            for (int i = 1; x >= tileWidth*i; i++)
                xIndex++;
            rightDistance = tileWidth*xIndex - xPos;
            break;
        }
    }
    return abs(leftDistance) <= rightDistance ? leftDistance : rightDistance;
}

/**
 * Finds the shortest absolute distance between a given position
 * and the nearest valid tile, relative to the y axis. Valid tiles
 * are 0 on the movementMatrix,and invalid ones are 1.
 * The distance will be negative if the closest valid tile is above
 * the position, and positive if below it.
 */
float MovementMap::FindYDistance(float xPos, float yPos)
{
    if (IsZero(xPos, yPos)) return 0;
    if ((xPos < 0 || xPos > mapWidth*tileWidth)) return 0;
    float aboveDistance = -999999, belowDistance = 999999;
    float y = yPos;
    // Checks for closest position above
    while (y > 0)
    {
        y = y - tileHeight;
        if (IsZero(xPos, y))
        {
            int yIndex = 0;
            for (int i = 1; y >= tileHeight*i; i++)
                yIndex++;
            aboveDistance = tileHeight*(yIndex+1) - yPos;
            break;
        }
    }
    // Checks for closest position below
    while (y < mapHeight * tileHeight)
    {
        y = y + tileHeight;
        if (IsZero(xPos, y))
        {
            int yIndex = 0;
            for (int i = 1; y >= tileHeight*i; i++)
                yIndex++;
            belowDistance = tileHeight*yIndex - yPos;
            break;
        }
    }
    return abs(aboveDistance) <= belowDistance ? aboveDistance : belowDistance;
}

/**
 * Sets the current layer of the movementMap
 */
void MovementMap::SetCurrentLayer(int layer)
{
    if (layer < 0 || layer >= mapDepth)
    {
        std::cerr << "Error! Invalid Layer Given!" << std::endl;
        return;
    }
    currentLayer = layer;
}
