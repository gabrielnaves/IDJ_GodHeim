/*
 * GateMov.cpp
 *
 *  Created on: Jul 6, 2014
 *      Author: icaro
 */

#include "../include/GateMov.h"

GateMov::GateMov()
{

}

void GateMov::UpdateSpeed(Character *character, float dt)
{
    if (character->vertical > 0) character->speed.Set(0,-VEL);
    else if (character->vertical < 0) character->speed.Set(0, VEL);
    else if (character->horizontal > 0) character->speed.Set(VEL,0);
    else if (character->horizontal < 0) character->speed.Set(-VEL,0);
    else character->speed.Set(0,0);
}

std::string GateMov::GetType()
{
	return ("Gate");
}
