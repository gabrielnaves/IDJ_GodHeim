/*
 * BrokenHouse.h
 *
 *  Created on: Jun 8, 2014
 *      Author: icaro
 *
 *  Description: A part of the cenario
 */

#ifndef BROKENHOUSE_H_
#define BROKENHOUSE_H_

#include "../../../engine/include/GameObject.h"
#include "../../../engine/include/Camera.h"
#include "../../../engine/include/Sprite.h"
#include "../../characters/include/Barrier.h"

class BrokenHouse : public GameObject
{
  public:
    BrokenHouse(float x, float y);
    virtual ~BrokenHouse();
    void Update(float dt);
    void RenderFront();
    void RenderBack();
    void Render();
    void NotifyCollision(GameObject& other);
    bool IsDead();
    bool Is(std::string type);
  private:
    Sprite frontHouseSp;
    Sprite backHouseSp;

    Point housePos;
};

#endif /* BROKENHOUSE_H_ */
