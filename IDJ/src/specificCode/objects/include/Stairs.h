/*
 * Stairs.h
 *
 *  Created on: Jun 8, 2014
 *      Author: Gabriel Naves
 */

#ifndef STAIRS_H_
#define STAIRS_H_

#include "../../../Engine.h"
#include "../../characters/include/Loki.h"
#include "../../characters/include/Thor.h"
#include <cmath>

class Stairs: public GameObject
{
  public:
    Stairs(std::string stairs, int x, int y);
    void Update(float dt);
    void Render();
    void NotifyCollision(GameObject& other);
    bool Is(std::string type);

  private:
    bool IsAboveStairs(Character *character);
    bool IsCloseToStairs(Character *character);
    bool IsStairsBelow(Rect character);
    bool IsStairsAbove(Rect character);
    void InteractsWith(Character *character);
    Sprite stairsSp;
};

#endif /* STAIRS_H_ */
