/*
 * BlockTileSet.cpp
 *
 *  Created on: Apr 24, 2014
 *      Author: Gabriel Naves
 */

#include "../include/BlockTileSet.h"

BlockTileSet::BlockTileSet(int tileWidth, int tileHeight, std::string file)
{
    this->tileWidth = tileWidth;
    this->tileHeight = tileHeight;
    Open(file);
}

void BlockTileSet::Open(std::string file)
{
    tileSet.Open(file);
    rows = tileSet.GetHeight();
    columns = tileSet.GetWidth();
}

void BlockTileSet::Render(unsigned int index, int x, int y)
{
    if (index >= 0 && (int)index < (columns/tileWidth)*(rows/tileHeight))
    {
        int tilePosX = 0, tilePosY = 0, quocient, remainder;

        ++index;
        quocient = index / (columns/tileWidth);
        remainder = index % (columns/tileWidth);

        if (remainder == 0)
        {
            remainder = (columns/tileWidth);
            quocient--;
        }
        remainder--;

        tilePosX = tilePosX + remainder * tileWidth;
        tilePosY = tilePosY + quocient * tileHeight;

        tileSet.SetClip(tilePosX, tilePosY, tileWidth, tileHeight);
        tileSet.Render(x, y);
    }
}
