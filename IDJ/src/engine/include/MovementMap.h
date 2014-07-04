/*
 * MovementMap.h
 *
 *  Created on: May 22, 2014
 *      Author: Gabriel Naves
 */

#ifndef MOVEMENTMAP_H_
#define MOVEMENTMAP_H_

#include "Collision.h"
#include "TileMap.h"
#include <algorithm>

class MovementMap
{
  public:
    MovementMap(std::string file, const TileSet& tileSet);
    int& At(int x, int y, int z = -1);
    bool IsZero(int x, int y, int layer = -1);
    void SetCurrentLayer(int layer);
    void UpdatePreviousPos(const Rect& rect);
    bool IsColliding(const Rect box);
    bool IsOnGround(const Rect box);
    Rect CorrectPosition(Rect box);
    void CorrectCollision(Rect& box, Rect tileBox);

    Point FindClosestVector(float xPos, float yPos, float angle = 0);
  private:
    std::vector<Rect> GetCollidingTiles(const Rect& box);
    void BuildMovementMap(std::string file);
    Rect TileToRect(float x, float y);
    void SortVector(std::vector<Rect> vector);
    bool SortCompare(Rect i, Rect j);

    float GetLeftDistance(float xPos, float yPos);
    float GetRightDistance(float xPos, float yPos);
    float GetUpperDistance(float xPos, float yPos);
    float GetLowerDistance(float xPos, float yPos);

    std::vector<int> movementMatrix;

    int mapWidth, mapHeight, mapDepth, currentLayer;
    int tileWidth, tileHeight;
    Rect previousPos;
};

#endif /* MOVEMENTMAP_H_ */
