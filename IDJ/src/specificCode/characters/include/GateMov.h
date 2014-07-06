/*
 * GateMov.h
 *
 *  Created on: Jul 6, 2014
 *      Author: icaro
 */

#ifndef GATEMOV_H_
#define GATEMOV_H_

#include "MovementState.h"

class GateMov : public MovementState
{
  public:
	GateMov();
    void UpdateSpeed(Character *character, float dt);
    std::string GetType();
};

#endif /* GATEMOV_H_ */
