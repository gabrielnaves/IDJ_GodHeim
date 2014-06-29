/*
 * MovementState.h
 *
 *  Created on: Jun 27, 2014
 *      Author: icaro
 *
 *  Description: Abstract class from which all movement patterns will be inherited from
 */

#ifndef MOVEMENTSTATE_H_
#define MOVEMENTSTATE_H_

#include "Character.h"

class MovementState
{
  public:
    virtual ~MovementState() {}
    virtual void UpdateSpeed(Character *character, float dt) = 0;
    virtual std::string GetType() = 0;
  protected:
    const float GRAVITY = 1000;
};

#endif /* MOVEMENTSTATE_H_ */
