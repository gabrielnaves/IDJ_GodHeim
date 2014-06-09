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
    MovementMap(std::string file, const TileSet& tileSet);
    int& At(int x, int y, int z = -1);
    bool IsZero(int x, int y, int layer = -1);
    Point FindClosestVector(float xPos, float yPos);
    void SetCurrentLayer(int layer);

  private:
    void BuildMovementMap(std::string file);
    float GetLeftDistance(float xPos, float yPos);
    float GetRightDistance(float xPos, float yPos);
    float GetUpperDistance(float xPos, float yPos);
    float GetLowerDistance(float xPos, float yPos);

    std::vector<int> movementMatrix;

    int mapWidth, mapHeight, mapDepth, currentLayer;
    int tileWidth, tileHeight;
};

#endif /* MOVEMENTMAP_H_ */
