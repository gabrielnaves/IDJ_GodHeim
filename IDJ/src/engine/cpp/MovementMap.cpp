/*
 * MovementMap.cpp
 *
 *  Created on: May 22, 2014
 *      Author: Gabriel Naves
 */

#include "../include/MovementMap.h"

MovementMap::MovementMap(std::string file, const TileSet& tileSet)
{
    tileWidth = tileSet.GetTileWidth();
    tileHeight = tileSet.GetTileHeight();
    currentLayer = 0;

    BuildMovementMap(file);
}

/**
 * Builds the movement map. The movement map consists of a
 * two-dimensional integer matrix, with values that can be 0 or 1,
 * 1 for the spaces on the map that cannot be walked into, 0 for the rest.
 */
void MovementMap::BuildMovementMap(std::string file)
{
    std::ifstream mapFile;
    mapFile.open(file);

    if (!mapFile.is_open())
    {
        std::cerr << "Could not open movementMap file." << std::endl;
        return;
    }

    std::string str;
    char a;
    mapFile >> this->mapWidth;
    mapFile >> a;
    mapFile >> this->mapHeight;
    mapFile >> a;
    mapFile >> this->mapDepth;
    getline(mapFile, str);
    getline(mapFile, str);

    int i = 0, j = 0, k = 0;
    std::string num;
    num.resize(2);
    movementMatrix.resize(mapWidth*mapHeight*mapDepth);
    for (unsigned int i = 0; i < movementMatrix.size(); i++) movementMatrix[i] = -1;

    while (getline(mapFile, str))
    {
        if (str.size() == 0)
        {
            ++k;
            i = j = 0;
            getline(mapFile, str);
        }
        while (str.size() > 1)
        {
            num[0] = str[0], num[1] = str[1];
            str.erase(0, 3);
            if (std::stoi(num) == 0) At(i, j, k) = 0;
            else At(i, j, k) = 1;
            ++i;
        }
        i = 0;
        ++j;
    }
}

int& MovementMap::At(int x, int y, int z)
{
    if (z == -1) z = currentLayer;
    return movementMatrix[x + mapWidth * y + mapWidth * mapHeight * z];
}

void MovementMap::UpdatePreviousPos(const Rect& rect)
{
    previousPos.Set(rect);
}

/**
 * Returns true if the value of the tile corresponding to
 * a given pixel position is 0, false if the value of the tile is 1.
 * If the given point is outside the limits of the map, returns false.
 * If the desired layer of the movement map is not given, it uses the
 * current one.
 */
bool MovementMap::IsZero(int x, int y, int layer)
{
    if (layer == -1) layer = currentLayer;
    if (x < 0 || x > mapWidth*tileWidth) return false;
    if (y < 0 || y > mapHeight*tileHeight) return false;
    int x_index=0, y_index=0;
    for (int i = 1; x >= tileWidth*i; i++)
        x_index++;
    for (int i = 1; y >= tileHeight*i; i++)
        y_index++;
    return At(x_index, y_index, layer) == 0 ? true : false;
}

/**
 * Returns the distance between a given position and the nearest
 * valid tile, looking to the left of the position.
 */
float MovementMap::GetLeftDistance(float xPos, float yPos)
{
    float x = xPos;
    while (x > 0)
    {
        x = x - tileWidth;
        if (IsZero(x, yPos))
        {
            int xIndex = 0;
            for (int i = 1; x >= tileWidth*i; i++)
                xIndex++;
            return tileWidth*(xIndex+1) - xPos;
        }
    }
    return -999999;
}

/**
 * Returns the distance between a given position and the nearest
 * valid tile, looking to the right of the position.
 */
float MovementMap::GetRightDistance(float xPos, float yPos)
{
    float x = xPos;
    while (x < mapWidth * tileWidth)
    {
        x = x + tileWidth;
        if (IsZero(x, yPos))
        {
            int xIndex = 0;
            for (int i = 1; x >= tileWidth*i; i++)
                xIndex++;
            return tileWidth*xIndex - xPos;
        }
    }
    return 999999;
}

/**
 * Returns the distance between a given position and the nearest
 * valid tile, looking up.
 */
float MovementMap::GetUpperDistance(float xPos, float yPos)
{
    float y = yPos;
    while (y > 0)
    {
        y = y - tileHeight;
        if (IsZero(xPos, y))
        {
            int yIndex = 0;
            for (int i = 1; y >= tileHeight*i; i++)
                yIndex++;
            return tileHeight*(yIndex+1) - yPos;
        }
    }
    return -999999;
}

/**
 * Returns the distance between a given position and the nearest
 * valid tile, looking down.
 */
float MovementMap::GetLowerDistance(float xPos, float yPos)
{
    float y = yPos;
    while (y < mapHeight * tileHeight)
    {
        y = y + tileHeight;
        if (IsZero(xPos, y))
        {
            int yIndex = 0;
            for (int i = 1; y >= tileHeight*i; i++)
                yIndex++;
            return tileHeight*yIndex - yPos;
        }
    }
    return 999999;
}

/**
 * Sets the current layer of the movementMap
 */
void MovementMap::SetCurrentLayer(int layer)
{
    if (layer < 0 || layer >= mapDepth)
    {
        std::cerr << "Error! Invalid Layer Given!" << std::endl;
        return;
    }
    currentLayer = layer;
}

Point MovementMap::FindClosestVector(float xPos, float yPos, float angle)
{
    Point result(99999, 99999);
    // Check if the position given is a valid tile
    if (IsZero(xPos, yPos)) return Point();
    // Look Right
    if (IsZero(xPos + tileWidth, yPos))
    {
        Point temp(GetRightDistance(xPos, yPos), 0);
        if (temp.Distance(Point()) < result.Distance(Point()))
            result = temp;
    }
    // Look Down-Right
    if (IsZero(xPos + tileWidth, yPos + tileHeight))
    {
        Point temp(GetRightDistance(xPos, yPos+tileHeight), GetLowerDistance(xPos+tileWidth, yPos));
        if (temp.Distance(Point()) < result.Distance(Point()))
            result = temp;
    }
    // Look Down
    if (IsZero(xPos, yPos + tileHeight))
    {
        Point temp(0, GetLowerDistance(xPos, yPos));
        if (temp.Distance(Point()) < result.Distance(Point()))
            result = temp;
    }
    // Look Down-Left
    if (IsZero(xPos - tileWidth, yPos + tileHeight))
    {
        Point temp(GetLeftDistance(xPos, yPos+tileHeight), GetLowerDistance(xPos-tileWidth, yPos));
        if (temp.Distance(Point()) < result.Distance(Point()))
            result = temp;
    }
    // Look Left
    if (IsZero(xPos - tileWidth, yPos))
    {
        Point temp(GetLeftDistance(xPos, yPos), 0);
        if (temp.Distance(Point()) < result.Distance(Point()))
            result = temp;
    }
    // Look Up-Left
    if (IsZero(xPos - tileWidth, yPos - tileHeight))
    {
        Point temp(GetLeftDistance(xPos, yPos-tileHeight), GetUpperDistance(xPos-tileWidth, yPos));
        if (temp.Distance(Point()) < result.Distance(Point()))
            result = temp;
    }
    // Look Up
    if (IsZero(xPos, yPos - tileHeight))
    {
        Point temp(0, GetUpperDistance(xPos, yPos));
        if (temp.Distance(Point()) < result.Distance(Point()))
            result = temp;
    }
    // Look Up-Right
    if (IsZero(xPos + tileWidth, yPos - tileHeight))
    {
        Point temp(GetRightDistance(xPos, yPos-tileHeight), GetUpperDistance(xPos+tileWidth, yPos));
        if (temp.Distance(Point()) < result.Distance(Point()))
            result = temp;
    }
    return result;
}

/**
 * This method uses the new position of the given object,
 * its previous position and the map to determine whether
 * the object is colliding with the walls
 */
bool MovementMap::IsColliding(const Rect box)
{
//    // Checks the center
//    if (!IsZero(box.Center().GetX(), box.Center().GetY())) return true;
    // Checks the above limit
    if (!IsZero(box.GetX()+box.GetW()/2, box.GetY())) return true;
    // Checks the right limit
    if (!IsZero(box.GetX() + box.GetW(), box.GetY() + box.GetH()/2)) return true;
    // Checks the left limit
    if (!IsZero(box.GetX(), box.GetY()+box.GetH()/2)) return true;
    // Checks the upper-right limit
    if (!IsZero(box.GetX()+box.GetW(), box.GetY())) return true;
    // Checks the upper-left limit
    if (!IsZero(box.GetX(), box.GetY())) return true;
    // Checks the lower limit
    if (!IsZero(box.Center().GetX(), box.Center().GetY() + box.GetH()/2)) return true;
    // Checks the lower-right limit
    if (!IsZero(box.GetX()+box.GetW(), box.GetY()+box.GetH())) return true;
    // Checks the lower-left limit
    if (!IsZero(box.GetX(), box.GetY()+box.GetH())) return true;
    return false;
//    return IsCollidingWithGround(box);
}

/**
 * Returns true if the given box is directly above the ground
 */
bool MovementMap::IsOnGround(const Rect box)
{
    // Checks the lower limit
    if (!IsZero(box.Center().GetX(), box.GetY()+box.GetH()+1)) return true;
    // Checks the lower-right limit
    if (!IsZero(box.GetX()+box.GetW(), box.GetY()+box.GetH()+1)) return true;
    // Checks the lower-left limit
    if (!IsZero(box.GetX(), box.GetY()+box.GetH()+1)) return true;
    return false;
}

/**
 * Corrects the box position so as not to collide with
 * the walls.
 */
Rect MovementMap::CorrectPosition(Rect box)
{
    std::cout << "Pos:(" << previousPos.GetX() << "," << previousPos.GetY() << ")" << std::endl;
    std::cout << "Width: " << previousPos.GetW() << std::endl;
    std::cout << "Height: " << previousPos.GetH() << std::endl;

    std::vector<Rect> collidingTiles;
    while (IsColliding(box))
    {
        collidingTiles = GetCollidingTiles(box);
        SortVector(collidingTiles);
        for (int i = 0; i < (int)collidingTiles.size(); i++)
            CorrectCollision(box, collidingTiles[i]);
        collidingTiles.clear();
        std::cout << "LOOP LULZ" << std::endl;
    }
    std::cout << "EXIT LOOP" << std::endl;
    return box;
}

/**
 * Returns a vector of Rects corresponding to the tiles
 * that are colliding with the given box
 */
std::vector<Rect> MovementMap::GetCollidingTiles(const Rect& box)
{
    std::vector<Rect> collidingTiles;
    // Check the upper point
    if (!IsZero(box.GetX()+box.GetW()/2, box.GetY()))
        collidingTiles.push_back(TileToRect(box.GetX(), box.GetY()));
    // Check the right point
    if (!IsZero(box.GetX()+box.GetW(), box.GetY()+box.GetH()/2))
        collidingTiles.push_back(TileToRect(box.GetX()+box.GetW(), box.GetY()));
    // Check the left point
    if (!IsZero(box.GetX(), box.GetY()+box.GetH()/2))
        collidingTiles.push_back(TileToRect(box.GetX(), box.GetY()+box.GetH()));
    // Check the lower point
    if (!IsZero(box.GetX()+box.GetW()/2, box.GetY()+box.GetH()))
        collidingTiles.push_back(TileToRect(box.GetX()+box.GetW(), box.GetY()+box.GetH()));
//    for (int i = 0; i < collidingTiles.size(); i++)
//    {
//        std::cout << std::endl;
//        std::cout << "(" << collidingTiles[i].GetX() << "," << collidingTiles[i].GetY() << ")" << std::endl;
//        std::cout << "Width: " << collidingTiles[i].GetW() << " Height: " << collidingTiles[i].GetH() << std::endl;
//    }
    return collidingTiles;
}

/**
 * Returns a Rect with the tile that is contained on the given
 * coordinates
 */
Rect MovementMap::TileToRect(float x, float y)
{
    float xPos = 0, yPos = 0;
    if (x > 0) while (abs(x-xPos) > tileWidth) xPos += tileWidth;
    else if (x < 0) while (abs(x-xPos) > tileWidth) xPos -=tileWidth;
    if (y > 0) while (abs(y-yPos) > tileHeight) yPos += tileHeight;
    else if (y < 0) while (abs(y-yPos) > tileHeight) yPos -=tileHeight;
//    std::cout << std::endl;
//    std::cout << "(" << xPos << "," << yPos << ")" << std::endl;
//    std::cout << "Width: " << tileWidth << " Height: " << tileHeight << std::endl;
    return Rect(xPos, yPos, tileWidth, tileHeight);
}

/**
 * Corrects the box position relative to a given tileBox
 * and the previous position of the box.
 */
void MovementMap::CorrectCollision(Rect& box, Rect tileBox)
{
    if (!Collision::IsColliding(box, tileBox, 0, 0)) return;
    // If the previous position was to the left of the tile
    if (previousPos.GetX()+previousPos.GetW() <= tileBox.GetX())
        box.MoveRect(tileBox.GetX() - (box.GetX()+box.GetW()), 0);
    // If the previous position was to the right of the tile
    else if (previousPos.GetX() >= tileBox.GetX()+tileBox.GetW())
        box.MoveRect((tileBox.GetX()+tileBox.GetW()) - box.GetX(), 0);
    // If the previous position was below the tile
    else if (previousPos.GetY() > tileBox.GetY())
        box.MoveRect(0, tileBox.GetY()+tileBox.GetH() - box.GetY());
    // If the previous position was above the tile
    else
        box.MoveRect(0, tileBox.GetY()-(box.GetY()+box.GetH()));
}

void MovementMap::SortVector(std::vector<Rect> collidingTiles)
{
    Rect aux;
    for (int j = collidingTiles.size(); j > 0; j--)
        for (int i = 0; i < j-1; i++)
            if (!SortCompare(collidingTiles[i], collidingTiles[i+1]))
            {
                aux = collidingTiles[i];
                collidingTiles[i] = collidingTiles[i+1];
                collidingTiles[i+1] = aux;
            }
}

bool MovementMap::SortCompare(Rect i, Rect j)
{
    if (i.Center().Distance(previousPos.Center()) < j.Center().Distance(previousPos.Center()))
        return true;
    return false;
}
