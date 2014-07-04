/*
 * HoldingWolf.h
 *
 *  Created on: Jul 4, 2014
 *      Author: icaro
 */

#ifndef HOLDINGWOLF_H_
#define HOLDINGWOLF_H_

#include "MovementState.h"

class HoldingWolf : public MovementState
{
  public:
    HoldingWolf();
    virtual ~HoldingWolf();
    void UpdateSpeed(Character *character, float dt);
    std::string GetType();
};

#endif /* HOLDINGWOLF_H_ */
