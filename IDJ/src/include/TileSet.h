/*
 * TileSet.h
 *
 *  Created on: Apr 4, 2014
 *      Author: Gabriel Naves
 */

#ifndef TILESET_H_
#define TILESET_H_

#include <iostream>
#include <string>

#include "Sprite.h"

class TileSet
{
  public:
    virtual ~TileSet();
    virtual void Open(std::string file) = 0;
    virtual void Render(unsigned int index, int x, int y) = 0;
    int GetTileWidth();
    int GetTileHeight();

  protected:
    int tileWidth;
    int tileHeight;
};

#endif /* TILESET_H_ */
