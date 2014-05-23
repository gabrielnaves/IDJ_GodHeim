/*
 * TileSet.h
 *
 *  Created on: Apr 4, 2014
 *      Author: Gabriel Naves
 *
 *  Description: Responsible for storing the tiles used for rendering the TileMap
 *
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
    int GetTileWidth() const;
    int GetTileHeight() const;

  protected:
    int tileWidth;
    int tileHeight;
};

#endif /* TILESET_H_ */
