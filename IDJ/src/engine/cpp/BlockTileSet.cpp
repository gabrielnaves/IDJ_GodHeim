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

/**
 * Returns the matrix position equivalent to the given index of the vector
 */
Point BlockTileSet::FindMatrixPos(unsigned int index)
{
	++index;
    int quocient = index / (columns/tileWidth);
    int remainder = index % (columns/tileWidth);

    if (remainder == 0)
    {
        remainder = (columns/tileWidth);
        quocient--;
    }
    remainder--;
	return(Point (remainder*tileWidth,quocient*tileHeight));
}


void BlockTileSet::Render(unsigned int index, int x, int y)
{
    if (index >= 0 && (int)index < (columns/tileWidth)*(rows/tileHeight))
    {
    	//Sets the position of the tile, so the program can render it
    	Point tilePos;
    	tilePos = tilePos + FindMatrixPos(index);

    	//Clips and renders.
        tileSet.SetClip(tilePos.GetX(), tilePos.GetY(), tileWidth, tileHeight);
        tileSet.Render(x, y);
    }
}
