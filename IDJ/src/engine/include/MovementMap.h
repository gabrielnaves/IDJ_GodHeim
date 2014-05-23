/*
 * MovementMap.h
 *
 *  Created on: May 22, 2014
 *      Author: Gabriel Naves
 */

#ifndef MOVEMENTMAP_H_
#define MOVEMENTMAP_H_

#include "TileMap.h"

class MovementMap
{
  public:
    MovementMap(std::string file, const TileSet& tileSet, int layer = 0);
    int& At(int x, int y);

  private:
    void BuildMovementMap(std::string file, int layer);

    std::vector<int> movementMatrix;

    int mapWidth, mapHeight;
    int tileWidth, tileHeight;
};

#endif /* MOVEMENTMAP_H_ */
