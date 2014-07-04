/*
 * HoldingWolf.cpp
 *
 *  Created on: Jul 4, 2014
 *      Author: icaro
 */

#include "../include/HoldingWolf.h"

HoldingWolf::HoldingWolf() {}

HoldingWolf::~HoldingWolf() {}

void HoldingWolf::UpdateSpeed(Character *character, float dt)
{
    character->speed.Set(0,0);
}

std::string HoldingWolf::GetType()
{
    return("HoldingWolf");
}
