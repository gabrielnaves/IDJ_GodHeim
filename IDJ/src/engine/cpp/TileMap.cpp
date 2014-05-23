/*
 * TileMap.cpp
 *
 *  Created on: Apr 4, 2014
 *      Author: Gabriel Naves
 */

#include "../include/TileMap.h"

TileMap::TileMap(int mapWidth, int mapHeight, int layers, TileSet* tileSet)
{
    this->mapWidth = mapWidth;
    this->mapHeight = mapHeight;
    this->mapDepth = layers;
    tileMatrix.resize(mapWidth*mapHeight*layers);
    this->tileSet = tileSet;
    for (unsigned int i = 0; i < tileMatrix.size(); i++) tileMatrix[i] = -1;
}

TileMap::TileMap(std::string file, TileSet* tileSet)
{
    Load(file);
    this->tileSet = tileSet;
}

void TileMap::Load(std::string file)
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
    tileMatrix.resize(mapWidth*mapHeight*mapDepth);
    for (unsigned int i = 0; i < tileMatrix.size(); i++) tileMatrix[i] = -1;

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
            At(i, j, k) = std::stoi(num)-1;
            ++i;
        }
        i = 0;
        ++j;
    }
}

void TileMap::SetTileSet(TileSet* tileSet)
{
    this->tileSet = tileSet;
}

int& TileMap::At(int x, int y, int z)
{
    return tileMatrix[x + mapWidth * y + mapWidth * mapHeight * z];
}

void TileMap::Render(int cameraX, int cameraY)
{
    for (int i = 0; i < mapDepth; ++i)
    {
        RenderLayer(i, cameraX, cameraY);
    }
}

void TileMap::RenderLayer(int layer, int cameraX, int cameraY)
{
    for (int j = 0, y = 0; j < mapHeight; j++)
    {
        for (int i = 0, x = 0; i < mapWidth; i++)
        {
            if (At(i, j, layer) != -1)
                tileSet->Render(At(i, j, layer), x - cameraX, y - cameraY);
            x = x + tileSet->GetTileWidth();
        }
        y = y + tileSet->GetTileHeight();
    }
}

int TileMap::GetWidth() const
{
    return mapWidth;
}

int TileMap::GetHeight() const
{
    return mapHeight;
}

int TileMap::GetDepth() const
{
    return mapDepth;
}

/**
 * Returns the index of the tile corresponding to a given pixel position.
 * If the given point is outside the limits of the map, returns -2.
 * (-1 means that there is no tile).
 */
int TileMap::GetTile(int x, int y, int layer)
{
    if (x < 0 || x > mapWidth*tileSet->GetTileWidth()) return -2;
    if (y < 0 || y > mapHeight*tileSet->GetTileHeight()) return -2;
    int x_index=0, y_index=0;
    for (int i = 1; x >= tileSet->GetTileWidth()*i; i++)
        x_index++;
    for (int i = 1; y >= tileSet->GetTileHeight()*i; i++)
        y_index++;
    return At(x_index, y_index, layer);
}
