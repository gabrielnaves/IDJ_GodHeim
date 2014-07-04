/*
 * Character.cpp
 *
 *  Created on: May 23, 2014
 *      Author: Icaro Mota
 *              Gabriel Naves
 */

#include "../include/Character.h"
#include "../include/Barrier.h"
#include "../include/RegularMov.h"
#include "../include/ClimbMov.h"
#include "../include/EagleMov.h"

Character::Character(MovementMap movMap,
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
    movement = new RegularMov();
    horizontal = vertical = 0;
    actionButton = false;
    insideBridge = false;
    aboveStairs = false;
    barrierSuspended = false;
    shouldRender = true;
}

void Character::Input()
{

    int UP_KEY = Is("Thor") ? SDLK_i:SDLK_w;
    int DOWN_KEY = Is("Thor") ? SDLK_k:SDLK_s;
    int LEFT_KEY = Is("Thor") ? SDLK_j:SDLK_a;
    int RIGHT_KEY = Is("Thor") ? SDLK_l:SDLK_d;
    int ACTION_BUTTON = Is("Thor") ? SDLK_u:SDLK_e;

    horizontal = vertical = 0;
    InputManager &input = InputManager::GetInstance();
    //Gets the inputs for moving horizontally
    if (input.KeyPress(RIGHT_KEY) || input.IsKeyDown(RIGHT_KEY))
        horizontal += 1;
    if (input.KeyPress(LEFT_KEY) || input.IsKeyDown(LEFT_KEY))
        horizontal -= 1;
    //Gets the inputs for moving vertically
    if (input.KeyPress(UP_KEY))
        vertical += 1;
    else if (input.IsKeyDown(UP_KEY))
        vertical = 2;
    if (input.KeyPress(DOWN_KEY) || input.IsKeyDown(DOWN_KEY))
        vertical -= 1;
    //Action button
    if (input.KeyPress(ACTION_BUTTON))
        actionButton = true;
}

void Character::Update(float dt)
{
    this->dt = dt;
    Input();
    Act();
    UpdateState();
    SelectMovState();
    movement->Move(this,dt);
    UpdatesStateOnTheFall();
    UpdateSprite();
    CheckMovementLimits();
    UpdatePrevState();
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

void Character::NotifyCollision(GameObject& other)
{
    if (other.Is("Spikes"))
        hp -= HP/20;
}

void Character::ChangeMovementState(std::string type)
{
    if (type == movement->GetType()) return;
    else delete movement;
    if (type == "Regular") movement = new RegularMov();
    else if (type == "Climb") movement = new ClimbMov();
    else if (type == "Eagle") movement = new EagleMov();
}

/**
 * Updates the vector speed accordingly to the vertical and horizontal state of the character.
 */
void Character::SelectMovState()
{
    if (not IndividualMovStateSelection())
    {
        if (actionState == CLIMBING)
            ChangeMovementState("Climb");
        else
            ChangeMovementState("Regular");
    }
}

/**
 * Characters have a few individual characteristics that might alter the way they update speed.
 * When they dont, returns false
 */
bool Character::IndividualMovStateSelection()
{
    return(false);
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
    	if (speed.GetY() >= 0)
    		SetVState(STANDING);
    	else
    		SetVState(JUMPING);
    }
    // If character speed > 0, then the character is falling
    else if ((!insideBridge) && (speed.GetY() >= 0) && (!aboveStairs))
    {
        SetVState(FALLING);
    }
    movementMap.UpdatePreviousPos(box);
}

bool Character::IsDead()
{
    return (hp <= 0 ? true : false);
}
bool Character::IsClimbing()
{
    return (actionState == CLIMBING ? true : false);
}
VerticalState Character::GetVState()
{
    return vState;
}
HorizontalState Character::GetHState()
{
    return hState;
}

void Character::CancelAction()
{
    SetActionState(NONE);
}
void Character::ReleasesStairs()
{
    SetActionState(NONE);
    SetVState(FALLING);
}
void Character::HoldStairs()
{
    SetActionState(CLIMBING);
}

/**
 * Updates the horizontal and vertical states of the character after receving input
 */
void Character::UpdateState()
{
    UpdateHorizontalState();
    UpdateVerticalState();
}
void Character::SetVState(VerticalState vS)
{
    prevVState = vState;
    vState = vS;
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
void Character::DealDamage(int damage)
{
    hp-=damage;
}
