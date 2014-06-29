/*
 * ClimbMov.h
 *
 *  Created on: Jun 28, 2014
 *      Author: icaro
 */

#ifndef CLIMBMOV_H_
#define CLIMBMOV_H_

#include "MovementState.h"

class ClimbMov : public MovementState
{
  public:
    ClimbMov();
    virtual ~ClimbMov();
    void UpdateSpeed(Character *character, float dt);
    std::string GetType();
  private:
    const float VEL = 200;
};

#endif /* CLIMBMOV_H_ */
