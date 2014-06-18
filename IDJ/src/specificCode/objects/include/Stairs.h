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
    Stairs(std::string stairs, int x, int y, int frameCount=1, float frameTime=0);
    virtual ~Stairs();
    void Update(float dt);
    void Render();
    void NotifyCollision(GameObject& other);
    bool Is(std::string type);

  private:
    void LookForCharacterAbove(Character *character);
    void ReleasesStairs(Character *character);
    Sprite stairsSp;
    bool showAnimation;
};

#endif /* STAIRS_H_ */
