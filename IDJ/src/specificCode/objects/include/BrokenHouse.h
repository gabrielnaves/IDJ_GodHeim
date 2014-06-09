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

class BrokenHouse : public GameObject
{
  public:
    BrokenHouse();
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
};

#endif /* BROKENHOUSE_H_ */
