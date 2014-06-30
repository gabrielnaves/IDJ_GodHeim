/*
 * EagleMov.h
 *
 *  Created on: Jun 29, 2014
 *      Author: icaro
 */

#ifndef EAGLEMOV_H_
#define EAGLEMOV_H_

#include "MovementState.h"
#include "../../../Engine.h"

class EagleMov : public MovementState
{
  public:
    EagleMov();
    virtual ~EagleMov();
    void UpdateSpeed(Character *character, float dt);
    std::string GetType();
  private:
    Timer transformTime;

    const float MAX_FALLING_SPEED_EAGLE = 100;
    const float EAGLE_JUMP_SPEED = -350;
    const float EAGLE_AIR_RESISTANCE = 200;
    const float TRANSFORM_COOLDOWN = 0.5;
};

#endif /* EAGLEMOV_H_ */
