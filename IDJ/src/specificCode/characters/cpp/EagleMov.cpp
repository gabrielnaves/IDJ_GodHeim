/*
 * EagleMov.cpp
 *
 *  Created on: Jun 29, 2014
 *      Author: icaro
 */

#include "../include/EagleMov.h"

EagleMov::EagleMov() {}

EagleMov::~EagleMov() {}

void EagleMov::UpdateSpeed(Character *character, float dt)
{
    if (character->GetVState() == JUST_JUMPED)
        character->speed.Set(character->speed.GetX(),EAGLE_JUMP_SPEED);
    //unnecessary if to follow. it is here only in case more vStates are implemented
    else if (character->GetVState() == FALLING or character->GetVState() == JUMPING)
        character->speed = character->speed + Point(character->speed.GetX(),(GRAVITY - EAGLE_AIR_RESISTANCE)*dt);

    if (character->GetHState() == STANDING_LEFT or character->GetHState() == STANDING_RIGHT)
        character->speed.Set(0,character->speed.GetY());
    else if (character->GetHState() == MOVING_RIGHT)
        character->speed.Set(VEL,character->speed.GetY());
    else if (character->GetHState() == MOVING_LEFT)
        character->speed.Set(-VEL,character->speed.GetY());

    if (character->speed.GetY() >= MAX_FALLING_SPEED_EAGLE)
        character->speed.Set(character->speed.GetX(), MAX_FALLING_SPEED_EAGLE);

    if (transformTime.Get() < TRANSFORM_COOLDOWN) character->speed.Set(0,0);
    transformTime.Update(dt);

    wingTime.Update(dt);
    if (wingTime.Get() > 1.1)
    {
    	wingTime.Restart();
        Sound flap("audio/Asa batendo game.ogg");
        flap.Play(0);
    }
}

std::string EagleMov::GetType()
{
    return("Eagle");
}
