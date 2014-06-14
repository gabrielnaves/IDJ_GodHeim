/*
 * Character.cpp
 *
 *  Created on: May 23, 2014
 *      Author: Icaro Mota
 *              Gabriel Naves
 */

#include "../include/Character.h"
#include "../include/Barrier.h"

Character::Character(MovementMap& movMap,std::string walk,int frameCount,float frameTime)
         : walkSp(walk,frameCount,frameTime), movementMap(movMap)
{
    hp = HP;
    rotation = 0;
    vState = STANDING;
    hState = STANDING_RIGHT;
    prevVState = vState;
    prevHState = hState;
    actionState = NONE;
    actionButton = false;
    horizontal = vertical = 0;
    canHoldStairs=false;
    insideBridge = false;
}

Point Character::GetSpeed()
{
    return(speed);
}

void Character::Render()
{
    SDL_RendererFlip flip = (hState == MOVING_RIGHT) or (hState == STANDING_RIGHT) ?  SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL;
    if (vState == STANDING and (hState == MOVING_RIGHT or hState == MOVING_LEFT))
        walkSp.Render(box.GetX()-Camera::pos.GetX(), box.GetY()-Camera::pos.GetY(),rotation, flip);
    else
        tempCharacterSp.Render(box.GetX()-Camera::pos.GetX(), box.GetY()-Camera::pos.GetY(),rotation, flip);
}

/**
 * Updates the vector speed when climbing stairs
 */
void Character::Climb(float dt)
{
    if (vertical == 0) speed.Set(speed.GetX(),0);
    if (vertical > 0) speed.Set(speed.GetX(),-VEL);
    if (vertical < 0) speed.Set(speed.GetX(), VEL);
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
    if (horizontal > 0) SetHState(MOVING_RIGHT);
    else if (horizontal < 0) SetHState(MOVING_LEFT);
    else (hState == MOVING_RIGHT or hState == STANDING_RIGHT) ? SetHState(STANDING_RIGHT) : SetHState(STANDING_LEFT);
}

/**
 * Updates the horizontal and vertical states of the character after receving input
 */
void Character::UpdateState()
{
    UpdateHorizontalState();
    UpdateVerticalState();
}

bool Character::IsClimbing()
{
    return (actionState == CLIMBING ? true : false);
}

void Character::CancelAction()
{
    actionState = NONE;
}

VerticalState Character::GetVState()
{
    return vState;
}

void Character::SetVState(VerticalState vS)
{
    prevVState = vState;
    vState = vS;
}

HorizontalState Character::GetHState()
{
    return hState;
}

void Character::SetHState(HorizontalState hS)
{
    prevHState = hState;
    hState = hS;
}

void Character::UpdatePrevState()
{
    prevHState = hState;
    prevVState = vState;
}

/**
 * Checks the limits of the cenario and stops the character from going into undesired places
 */
void Character::CheckMovementLimits()
{
    Point movementVector;
    // Checks the above limit
    if (!movementMap.IsZero(box.Center().GetX(), box.Center().GetY() - box.GetH()/2))
    {
        speed.Set(speed.GetX(),0);
        box.MoveRect(movementMap.FindClosestVector(box.Center().GetX(), box.Center().GetY() - box.GetH()/2));
    }
    // Checks the lower-right limit
    if (!movementMap.IsZero(box.GetX()+box.GetW(), box.GetY()+box.GetH()))
    {
        movementVector.Set(movementMap.FindClosestVector(box.GetX()+box.GetW(), box.GetY()+box.GetH()));
        box.MoveRect(movementVector);
    }
    // Checks the lower-left limit
    if (!movementMap.IsZero(box.GetX(), box.GetY()+box.GetH()))
    {
        movementVector.Set(movementMap.FindClosestVector(box.GetX(), box.GetY()+box.GetH()));
        box.MoveRect(movementVector);
    }
    // Checks the upper-right limit
    if (!movementMap.IsZero(box.GetX()+box.GetW(), box.GetY()))
    {
        movementVector.Set(movementMap.FindClosestVector(box.GetX()+box.GetW(), box.GetY()));
        box.MoveRect(movementVector);
    }
    // Checks the upper-left limit
    if (!movementMap.IsZero(box.GetX(), box.GetY()))
    {
        movementVector.Set(movementMap.FindClosestVector(box.GetX(), box.GetY()));
        box.MoveRect(movementVector);
    }
    // Checks the right limit
    if (!movementMap.IsZero(box.Center().GetX() + box.GetW()/2, box.Center().GetY()))
        box.MoveRect(movementMap.FindClosestVector(box.Center().GetX() + box.GetW()/2, box.Center().GetY()));
    // Checks the left limit
    if (!movementMap.IsZero(box.Center().GetX() - box.GetW()/2, box.Center().GetY()))
        box.MoveRect(movementMap.FindClosestVector(box.Center().GetX() - box.GetW()/2, box.Center().GetY()));
    // Checks the lower limit
    if (!movementMap.IsZero(box.Center().GetX(), box.Center().GetY() + box.GetH()/2))
    {
        box.MoveRect(movementMap.FindClosestVector(box.Center().GetX(), box.Center().GetY() + box.GetH()/2));
        SetVState(STANDING);
    }
    else if (!insideBridge)
    {
        SetVState(FALLING);
    }
}
