/*
 * TileSet.cpp
 *
 *  Created on: Apr 4, 2014
 *      Author: Gabriel Naves
 */

#include "../include/TileSet.h"

TileSet::~TileSet()
{
}

int TileSet::GetTileWidth() const
{
    return tileWidth;
}

int TileSet::GetTileHeight() const
{
    return tileHeight;
}
