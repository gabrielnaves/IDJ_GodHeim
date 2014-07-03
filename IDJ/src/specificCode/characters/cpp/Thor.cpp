/*
 * Thor.cpp
 *
 *  Created on: May 19, 2014
 *      Author: Gabriel Naves
 *              Icaro Mota
 */

#include "../include/Thor.h"

Thor* Thor::characterThor;

Thor::Thor(float x, float y, MovementMap& movMap) :
        Character(movMap,"img/characters/thor_walk.png",7,0.1,"img/characters/thor_jump.png",4,0.1,"img/characters/thorStairs.png",2,0.15)
{
    characterSp.Open("img/characters/thor.png");
    box.Set(x-characterSp.GetWidth()/2, y-characterSp.GetHeight()/2, characterSp.GetWidth(), characterSp.GetHeight());
    characterThor = this;
}

Thor::~Thor()
{
    characterThor = NULL;
}

/**
 * Calls the right action Thor must do, depending on the situation
 */
void Thor::Act()
{
    if (!actionButton) return;

    actionButton = false;
}

void Thor::Hit()
{

}

void Thor::UpdateVerticalState()
{
	// If character center is below 9/10 of the barrier, then the character is suspended.
	if ( ((Barrier::barrier->GetCorner().GetY()+(Barrier::barrier->DIAMETER*9/10)) < box.Center().GetY())
			&& (box.Center().Distance(Loki::characterLoki->box.Center()) >= Barrier::barrier->DIAMETER - Barrier::barrier->DRAG_TOLERANCE))
		barrierSuspended = true;
	else
		barrierSuspended = false;


    if (vertical == 1 and vState == STANDING)
        SetVState(JUST_JUMPED);
}

void Thor::UpdatesStateOnTheFall()
{
    if (vState == JUST_JUMPED) SetVState(JUMPING);
    if (speed.GetY() > 0) SetVState(FALLING);
}

bool Thor::Is(std::string type)
{
    return type == "Thor" ? true : false;
}

/**
 * Updates the sprite based on the state of the character
 */
void Thor::UpdateSprite()
{
    if (vState == STANDING)
    {
        if (hState == MOVING_RIGHT or hState == MOVING_LEFT)
            prevHState != hState ? ChangeSp("walkSp","img/characters/thor_walk.png",7) : walkSp.Update(dt);
        else if (hState == STANDING_RIGHT or hState == STANDING_LEFT)
            ChangeSp("characterSp","img/characters/thor.png",1);
    }
    else if (actionState == CLIMBING)
    {
        if (prevActionState != CLIMBING)
            ChangeSp("climbSp","img/characters/lokiStairs.png",2);
        else if (vertical != 0)
            climbSp.Update(dt);
    }
    else if (vState == FALLING)
                ChangeSp("jumpSp","img/characters/thor_jump.png",4,4,false);
            else if (vState == JUMPING)
            {
                if (prevVState == JUST_JUMPED)
                    ChangeSp("jumpSp","img/characters/thor_jump.png",4,1,false);
                else
                    jumpSp.Update(dt);
            }
}
