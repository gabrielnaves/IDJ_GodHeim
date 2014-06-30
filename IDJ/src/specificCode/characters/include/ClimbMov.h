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
};

#endif /* CLIMBMOV_H_ */
