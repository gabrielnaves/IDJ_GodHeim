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
 * Returns true if the value of the tile corresponding to
 * a given pixel position is 0, false if the value of the tile is 1.
 * If the given point is outside the limits of the map, returns false.
 */
bool MovementMap::IsZero(int x, int y)
{
    if (x < 0 || x > mapWidth*tileWidth) return false;
    if (y < 0 || y > mapHeight*tileHeight) return false;
    int x_index=0, y_index=0;
    for (int i = 1; x >= tileWidth*i; i++)
        x_index++;
    for (int i = 1; y >= tileHeight*i; i++)
        y_index++;
    return At(x_index, y_index) == 0 ? true : false;
}

/**
 * Finds the shortest absolute distance between a given position
 * and the nearest valid tile, relative to the x axis. Valid tiles
 * are 0 on the movementMatrix,and invalid ones are 1.
 * The distance will be negative if the closest valid tile is to the left
 * of the position, and positive if to the right.
 */
int MovementMap::FindXDistance(int xPos, int yPos)
{
    if (IsZero(xPos, yPos)) return 0;
    if ((yPos < 0 || yPos > mapHeight*tileHeight)) return 0;
    int leftDistance = -999999, rightDistance = 999999;
    int x = xPos;
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
    return fabs(leftDistance) <= rightDistance ? leftDistance : rightDistance;
}

/**
 * Finds the shortest absolute distance between a given position
 * and the nearest valid tile, relative to the y axis. Valid tiles
 * are 0 on the movementMatrix,and invalid ones are 1.
 * The distance will be negative if the closest valid tile is above
 * the position, and positive if below it.
 */
int MovementMap::FindYDistance(int xPos, int yPos)
{
    if (IsZero(xPos, yPos)) return 0;
    if ((xPos < 0 || xPos > mapWidth*tileWidth)) return 0;
    int aboveDistance = -999999, belowDistance = 999999;
    int y = yPos;
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
    return fabs(aboveDistance) <= belowDistance ? aboveDistance : belowDistance;
}
