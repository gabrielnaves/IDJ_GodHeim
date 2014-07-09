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
    bool IsStairsBelow(Rect character);
    void InteractsWith(Character *character);
    bool ShouldStandOnStairs(Character *character);
    void Stand(Character *character);
    bool IsCloseTo(Character *character);
    bool CanClimb(Character *character);
    bool ShouldDrop(Character *character);
    void Drop(Character *character);
    Sprite stairsSp;
    Rect prevThor;
    Rect prevLoki;
};

#endif /* STAIRS_H_ */
