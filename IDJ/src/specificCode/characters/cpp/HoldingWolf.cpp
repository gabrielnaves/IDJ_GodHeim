/*
 * HoldingWolf.cpp
 *
 *  Created on: Jul 4, 2014
 *      Author: icaro
 */

#include "../include/HoldingWolf.h"

HoldingWolf::HoldingWolf()
{
    thorHState = Thor::characterThor->GetHState();
}

HoldingWolf::~HoldingWolf() {}

void HoldingWolf::UpdateSpeed(Character *character, float dt)
{
    character->SetHState(thorHState);
    character->speed.Set(character->horizontal*VEL/5,0);
}

std::string HoldingWolf::GetType()
{
    return("HoldingWolf");
}
