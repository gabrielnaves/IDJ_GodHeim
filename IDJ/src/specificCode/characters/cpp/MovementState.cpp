/*
 * MovementState.cpp
 *
 *  Created on: Jun 30, 2014
 *      Author: icaro
 */

#include "../include/MovementState.h"

void MovementState::Move(Character *character, float dt)
{
    UpdateSpeed(character,dt);
    character->box.MoveRect(character->speed.GetX()*dt,character->speed.GetY()*dt);
    Barrier::barrier->CheckCollision(character);
}
