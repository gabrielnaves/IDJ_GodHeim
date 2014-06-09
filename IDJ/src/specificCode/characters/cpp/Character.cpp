/*
 * Character.cpp
 *
 *  Created on: May 23, 2014
 *      Author: Icaro Mota
 *              Gabriel Naves
 */

#include "../include/Character.h"
#include "../include/Barrier.h"

Character::Character(MovementMap& movMap) : movementMap(movMap)
{
    hp = 100;
    vState = STANDING;
    hState = STANDING_RIGHT;
    actionButton = false;
    horizontal = vertical = 0;
    canUseStairs=false;
}

Point Character::GetSpeed()
{
    return(speed);
}

/**
 * Updates the vector speed accordingly to the state of the character.
 */
void Character::UpdateSpeed(float dt)
{
    //Updates the vertical state
    if (vState == STANDING) speed.Set(speed.GetX(),0);
    else if (vState == JUST_JUMPED) speed.Set(speed.GetX(),JUMP_SPEED);
    else if (vState == FALLING or vState == JUMPING) speed = speed + Point(speed.GetX(),GRAVITY*dt);
    else if (vState == CLIMBING) speed.Set(0,speed.GetY());

    //Sets a limit to the falling speed
    if (speed.GetY() >= MAX_FALLING_SPEED) speed.Set(speed.GetX(), MAX_FALLING_SPEED);

    //Updates the horizontal state
    if (hState == STANDING_LEFT or hState == STANDING_RIGHT) speed.Set(0,speed.GetY());
    else if (hState == MOVING_RIGHT) speed.Set(VEL,speed.GetY());
    else if (hState == MOVING_LEFT) speed.Set(-VEL,speed.GetY());
}

bool Character::IsDead()
{
    return (hp <= 0 ? true : false);
}

/**
 * Updates the state of the horizontal movement based on the input.
 * If the user presses both the left and right buttons, the character will not move.
 */
void Character::UpdateHorizontalState()
{
    if (horizontal > 0) hState = MOVING_RIGHT;
    else if (horizontal < 0) hState = MOVING_LEFT;
    else (hState == MOVING_RIGHT or hState == STANDING_RIGHT) ? hState = STANDING_RIGHT : hState = STANDING_LEFT;
}

/**
 * Updates the horizontal and vertical states of the character after receving input
 */
void Character::UpdateState()
{
    UpdateHorizontalState();
    UpdateVerticalState();
}

/**
 * Checks the limits of the cenario and stops the character from going into undesired places
 */
void Character::CheckMovementLimits()
{
    // Checks the right limit
    if (!movementMap.IsZero(box.Center().GetX() + box.GetW()/2, box.Center().GetY()))
        box.MoveRect(movementMap.FindXDistance(box.Center().GetX() + box.GetW()/2, box.Center().GetY()),0);
    // Checks the left limit
    if (!movementMap.IsZero(box.Center().GetX() - box.GetW()/2, box.Center().GetY()))
        box.MoveRect(movementMap.FindXDistance(box.Center().GetX() - box.GetW()/2, box.Center().GetY()),0);
    // Checks the above limit
    if (!movementMap.IsZero(box.Center().GetX(), box.Center().GetY() - box.GetH()/2))
        box.MoveRect(0,movementMap.FindYDistance(box.Center().GetX(), box.Center().GetY() - box.GetH()/2));
    // Checks the lower limit
    if (!movementMap.IsZero(box.Center().GetX(), box.Center().GetY() + box.GetH()/2))
    {
        box.MoveRect(0,movementMap.FindYDistance(box.Center().GetX(), box.Center().GetY() + box.GetH()/2));
        vState = STANDING;
    }
    else vState = FALLING;
}
