/*
 * BrokenHouse.h
 *
 *  Created on: Jun 8, 2014
 *      Author: icaro
 *
 *  Description: A part of the cenario
 */

#ifndef BROKENHOUSEFRONT_H_
#define BROKENHOUSEFRONT_H_

#include "../../../Engine.h"
#include "../../characters/include/Barrier.h"

class BrokenHouseFront : public GameObject
{
  public:
    BrokenHouseFront(float x, float y);
    virtual ~BrokenHouseFront();
    void Update(float dt);
    void Render();
    bool Is(std::string type);
  private:
    Sprite frontHouseSp;

    Point housePos;
};

#endif /* BROKENHOUSEFRONT_H_ */
