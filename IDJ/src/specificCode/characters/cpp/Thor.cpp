/*
 * Thor.cpp
 *
 *  Created on: May 19, 2014
 *      Author: Gabriel Naves
 *              Icaro Mota
 */

#include "../include/Thor.h"
#include "../../gameStates/include/StateData.h"

Thor* Thor::characterThor;

Thor::Thor(float x, float y, MovementMap movMap) :
        Character(movMap,"img/characters/thor_walk.png",8,0.1,"img/characters/thor_jump.png",4,0.1,"img/characters/thorStairs.png",3,0.15,
        		"img/characters/hitthor.png")
{
	characterSp.Open("img/characters/thor.png");
	if (StateData::checkpoint && StateData::thorBox.GetX() && StateData::thorBox.GetY())
		box.Set(StateData::thorBox.GetX(), StateData::thorBox.GetY(), characterSp.GetWidth(), characterSp.GetHeight());
	else
		box.Set(x-characterSp.GetWidth()/2, y-characterSp.GetHeight()/2, characterSp.GetWidth(), characterSp.GetHeight());
    characterThor = this;
    this->movementMap.UpdatePreviousPos(box);
    canHoldWolf = false;
	hp.emplace_back(new HpBar("img/characters/thorHp.png","Thor",1100,10));
    for (int i=1;i<3;i++)
    	hp.emplace_back(new HpBar(hp[i-1]->GetSp(),hp[i-1]->GetCharacter(),
    					hp[i-1]->box.GetX()+hp[i-1]->box.GetW(),hp[i-1]->box.GetY()));
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
	if (actionState == JUST_ATTACKED) SetActionState(ATTACKING);
    hitting.Update(dt);
    if (!actionButton) return;
    if (actionState == ATTACKING and hitting.Get() < HITTING_COOLDOWN) return;
    else if (actionState == ATTACKING and hitting.Get() > HITTING_COOLDOWN) SetActionState(NONE);

    // Debug Comments
    //if (canPressSwitch) printf("Can press switch\n");
    //if (ItemFlags::shield) printf("Has shield\n");
    //if (ItemFlags::hammer) printf("Has hammer\n");
    //if (canHoldWolf) printf("Can Hold Wolf\n");

    if (canPressSwitch)
        pressSwitch = true;
    else if (ItemFlags::shield and GetMovementType() == "HoldingWolf")
        ChangeMovementState("Regular"); //if he is holding the wolf, releases it
    else if (ItemFlags::shield and canHoldWolf)
        ChangeMovementState("HoldingWolf"); //if he can hold the wolf, holds it
    else if (ItemFlags::hammer)
    	Hit();

    actionButton = false;
}


bool Thor::IndividualMovStateSelection()
{
    if (canHoldWolf and GetMovementType() == "HoldingWolf") return true;
    return false;
}

void Thor::Hit()
{
	hitting.Restart();
	SetActionState(JUST_ATTACKED);
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
    if (GetMovementType() == "HoldingWolf")
        ChangeSp("characterSp","img/characters/thorShield.png",1);
    else if (vState == STANDING)
    {
        if ((hState == MOVING_RIGHT or hState == MOVING_LEFT) and !ItemFlags::hammer)
            prevHState != hState ? ChangeSp("walkSp","img/characters/thor_walk.png",8) : walkSp.Update(dt);
        else if ((hState == MOVING_RIGHT or hState == MOVING_LEFT) and ItemFlags::hammer)
        	prevHState != hState ? ChangeSp("walkSp","img/characters/thorpinturacaminhamartelospritsheet.png",7) : walkSp.Update(dt);
        else if ((hState == STANDING_RIGHT or hState == STANDING_LEFT) and !ItemFlags::hammer)
            ChangeSp("characterSp","img/characters/thor.png",1);
        else if ((hState == STANDING_RIGHT or hState == STANDING_LEFT) and ItemFlags::hammer)
            ChangeSp("characterSp","img/characters/thorHammer.png",1);
    }
    else if (actionState == CLIMBING)
    {
        if (prevActionState != CLIMBING)
            ChangeSp("climbSp","img/characters/lokiStairs.png",2);
        else if (vertical != 0)
            climbSp.Update(dt);
    }
    else if (actionState == CLIMBING_GATE)
    {
        if (prevActionState != CLIMBING_GATE)
            ChangeSp("climbSp","img/characters/lokiStairs.png",2);
        else if (vertical != 0 or horizontal != 0)
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
