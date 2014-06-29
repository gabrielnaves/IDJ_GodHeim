/*
 * RegularMov.cpp
 *
 *  Created on: Jun 28, 2014
 *      Author: icaro
 */

#include "../include/RegularMov.h"

RegularMov::RegularMov() {}

RegularMov::~RegularMov() {}

void RegularMov::UpdateSpeed(Character *character, float dt)
{
    //Updates the vertical state
    if (character->GetVState() == STANDING)
        character->speed.Set(character->speed.GetX(),0);
    else if (character->GetVState() == JUST_JUMPED)
        character->speed.Set(character->speed.GetX(),JUMP_SPEED);
    else if (character->GetVState() == FALLING or character->GetVState() == JUMPING)
        character->speed = character->speed + Point(character->speed.GetX(),GRAVITY*dt);

    //Sets a limit to the falling speed
    if (character->speed.GetY() >= MAX_FALLING_SPEED)
        character->speed.Set(character->speed.GetX(), MAX_FALLING_SPEED);

    //Updates the horizontal state
    if (character->GetHState() == STANDING_LEFT or character->GetHState() == STANDING_RIGHT)
        character->speed.Set(0,character->speed.GetY());
    else if (character->GetHState() == MOVING_RIGHT) character->speed.Set(VEL,character->speed.GetY());
    else if (character->GetHState() == MOVING_LEFT) character->speed.Set(-VEL,character->speed.GetY());
}

std::string RegularMov::GetType()
{
    return("Regular");
}
