/*
 * RegularMov.h
 *
 *  Created on: Jun 28, 2014
 *      Author: icaro
 */

#ifndef REGULARMOV_H_
#define REGULARMOV_H_

#include "MovementState.h"

class RegularMov : public MovementState
{
  public:
    RegularMov();
    virtual ~RegularMov();
    void UpdateSpeed(Character *character, float dt);
    std::string GetType();
  private:
    const float JUMP_SPEED = -500;
    const float MAX_FALLING_SPEED = 600;
};

#endif /* REGULARMOV_H_ */
