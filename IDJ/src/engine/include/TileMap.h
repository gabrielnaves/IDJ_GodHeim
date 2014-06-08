/*
 * TileMap.h
 *
 *  Created on: Apr 4, 2014
 *      Author: Gabriel Naves
 *
 *  Description: Simulates a 3D matrix, representing the map and its layers.
 *  			 It contains, in each position, an index of tile in TileSet
 *
 */

#ifndef TILEMAP_H_
#define TILEMAP_H_

#include "TileSet.h"

class TileMap
{
  public:
    TileMap(int mapWidth, int mapHeight, int layers, TileSet* tileSet = NULL);
    TileMap(std::string file, TileSet* tileSet = NULL);
    void Load(std::string file);
    void SetTileSet(TileSet* tileSet);
    int& At(int x, int y, int z = 0);
    void Render(int cameraX = 0, int cameraY = 0);
    void RenderLayer(int layer, int cameraX = 0, int cameraY = 0);

    int GetWidth() const;
    int GetHeight() const;
    int GetDepth() const;

    bool HasTile(int x, int y, int layer);

  private:
    std::vector<int> tileMatrix;
    TileSet* tileSet;
    int mapWidth;
    int mapHeight;
    int mapDepth;
};

#endif /* TILEMAP_H_ */
