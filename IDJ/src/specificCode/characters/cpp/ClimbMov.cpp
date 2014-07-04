/*
 * ClimbMov.cpp
 *
 *  Created on: Jun 28, 2014
 *      Author: icaro
 */

#include "../include/ClimbMov.h"

ClimbMov::ClimbMov() {}

ClimbMov::~ClimbMov() {}

void ClimbMov::UpdateSpeed(Character *character, float dt)
{
    if (character->vertical == 0) character->speed.Set(0,0);
    if (character->vertical > 0) character->speed.Set(0,-VEL);
    if (character->vertical < 0) character->speed.Set(0, VEL);
}

std::string ClimbMov::GetType()
{
    return("Climb");
}
