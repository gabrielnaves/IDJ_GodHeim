/*
 * MultiTileSet.h
 *
 *  Created on: Apr 4, 2014
 *      Author: Gabriel Naves
 */

#ifndef MULTITILESET_H_
#define MULTITILESET_H_

#include "TileSet.h"

class MultiTileSet: public TileSet
{
  public:
    MultiTileSet(int tileWidth, int tileHeight);
    virtual ~MultiTileSet();
    void Open(std::string file);
    void Render(unsigned int index, int x, int y);

  protected:
    std::vector<Sprite> tileArray;

};

#endif /* MULTITILESET_H_ */
