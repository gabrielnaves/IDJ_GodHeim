/*
 * Character.cpp
 *
 *  Created on: May 23, 2014
 *      Author: Icaro Mota
 *              Gabriel Naves
 */

#include "../include/Character.h"
#include "../include/Barrier.h"

Character::Character(MovementMap& movMap,
           std::string walk,int wFrameCount,float wFrameTime,
           std::string jump,int jFrameCount,float jFrameTime,
           std::string climb, int cFrameCount, float cFrameTime)
         : walkSp(walk,wFrameCount,wFrameTime),
           jumpSp(jump,jFrameCount,jFrameTime,false),
           climbSp(climb,cFrameCount,cFrameTime),
           movementMap(movMap)
{
    hp = HP;
    rotation = 0;
    dt = 0;
    SetVState(STANDING);
    SetHState(STANDING_RIGHT);
    SetActionState(NONE);
    horizontal = vertical = 0;
    actionButton = false;
    canHoldStairs=false;
    insideBridge = false;
    barrierSuspended = false;
    shouldRender = true;
}

void Character::Update(float dt)
{
    this->dt = dt;
    Input();
    Act();
    UpdateState();
    if (actionState == CLIMBING and !canHoldStairs) SetActionState(NONE);
    Move();
    UpdatesStateOnTheFall();
    UpdateSprite();
    CheckMovementLimits();
    UpdatePrevState();
}

Point Character::GetSpeed()
{
    return(speed);
}

/**
 * Renders a different image of the character on the screen depending on the state
 */
void Character::Render()
{
    if (not shouldRender) return;
    SDL_RendererFlip flip = (hState == MOVING_RIGHT) or (hState == STANDING_RIGHT) ?  SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL;
    if (vState == STANDING and (hState == MOVING_RIGHT or hState == MOVING_LEFT))
        walkSp.Render(box.GetX()-Camera::pos.GetX(), box.GetY()-Camera::pos.GetY(),rotation, flip);
    else if (actionState == CLIMBING)
        climbSp.Render(box.GetX()-Camera::pos.GetX(), box.GetY()-Camera::pos.GetY(),rotation);
    else if (vState == JUST_JUMPED or vState == JUMPING or vState == FALLING)
        jumpSp.Render(box.GetX()-Camera::pos.GetX(), box.GetY()-Camera::pos.GetY(),rotation, flip);
    else
        characterSp.Render(box.GetX()-Camera::pos.GetX(), box.GetY()-Camera::pos.GetY(),rotation, flip);
}

/**
 * Updates the vector speed when climbing stairs
 */
void Character::Climb()
{
    if (vertical == 0) speed.Set(speed.GetX(),0);
    if (vertical > 0) speed.Set(speed.GetX(),-VEL);
    if (vertical < 0) speed.Set(speed.GetX(), VEL);
}

/**
 * Updates the vector speed accordingly to the state of the character.
 */
void Character::UpdateSpeed()
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

void Character::ReleasesStairs()
{
    SetActionState(NONE);
    SetVState(FALLING);
}

void Character::HoldStairs()
{
    SetActionState(CLIMBING);
    box.SetPoint(box.GetPoint().GetX(),box.GetPoint().GetY()+1);
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
    SetActionState(NONE);
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
void Character::SetActionState(ActionState actionState)
{
    prevActionState = actionState;
    this->actionState = actionState;
}

void Character::ChangeSp(std::string spType, std::string sp, int frameCount, int currentFrame, bool repeat)
{
    if (spType == "characterSp")
    {
        characterSp.SetFrameCount(frameCount);
        characterSp.SetFrame(currentFrame);
//        box.Set(box.GetX(), box.GetY(), characterSp.GetWidth(), characterSp.GetHeight());
    }
    else if (spType == "walkSp")
    {
        walkSp.SetFrameCount(frameCount);
        walkSp.SetFrame(currentFrame);
//        box.Set(box.GetX(), box.GetY(), walkSp.GetWidth(), walkSp.GetHeight());
    }
    else if (spType == "jumpSp")
    {
        jumpSp.Open(sp);
        jumpSp.SetFrameCount(frameCount);
        jumpSp.SetFrame(currentFrame);
        jumpSp.SetRepeat(repeat);
//        box.Set(box.GetX(), box.GetY(), jumpSp.GetWidth(), jumpSp.GetHeight());
    }
    else if (spType == "climbSp")
    {
        climbSp.SetFrameCount(frameCount);
        climbSp.SetFrame(currentFrame);
//        box.Set(box.GetX(), box.GetY(), climbSp.GetWidth(), climbSp.GetHeight());
    }
}

/**
 * Checks the limits of the scenario and stops the character from going into undesired places
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
    // Checks if the barrier is suspending the character
    else if (barrierSuspended)
    {
    	if (GetSpeed().GetY() >= 0)
    		SetVState(STANDING);
    	else
    		SetVState(JUMPING);
    }

    // If character speed > 0, then the character is falling
    else if ((!insideBridge) && (GetSpeed().GetY() >= 0))
    {
        SetVState(FALLING);
    }
}
