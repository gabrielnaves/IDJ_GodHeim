/*
 * MultiTileSet.cpp
 *
 *  Created on: Apr 4, 2014
 *      Author: Gabriel Naves
 */

#include "../include/MultiTileSet.h"

MultiTileSet::MultiTileSet(int tileWidth, int tileHeight)
{
    this->tileWidth = tileWidth;
    this->tileHeight = tileHeight;
}

MultiTileSet::~MultiTileSet()
{
    tileArray.clear();
}

void MultiTileSet::Open(std::string file)
{
    tileArray.emplace_back(file);
}

void MultiTileSet::Render(unsigned int index, int x, int y)
{
    if (index >= 0 && index < tileArray.size())
        tileArray[index].Render(x, y);
}
