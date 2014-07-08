/*
 * Loki.cpp
 *
 *  Created on: May 19, 2014
 *      Author: Gabriel Naves
 *              Icaro Mota
 */

#include "../include/Loki.h"
#include "../include/EagleMov.h"

Loki* Loki::characterLoki;

Loki::Loki(float x, float y, MovementMap movMap) :
        Character(movMap,"img/characters/loki_walk.png",7,0.1,"img/characters/lokiJump.png",4,0.1,"img/characters/lokiStairs.png",3,0.15,
        		"img/characters/lokihit.png")
{
	characterSp.Open("img/characters/loki.png");
	box.Set(x-characterSp.GetWidth()/2, y-characterSp.GetHeight()/2, characterSp.GetWidth(), characterSp.GetHeight());
	characterLoki = this;
	appearance = prevAppearance = LOKI;
	flappedWings = 0;
	TIMES_FLAPS_WINGS = 1;
	this->movementMap.UpdatePreviousPos(box);
	cannotTransform = false;
	hp.emplace_back(new HpBar("img/characters/lokiHp.png","Loki",10,10));
    for (int i=1;i<3;i++)
    	hp.emplace_back(new HpBar(hp[i-1]->GetSp(),hp[i-1]->GetCharacter(),
    					hp[i-1]->box.GetX()+hp[i-1]->box.GetW(),hp[i-1]->box.GetY()));
}

Loki::~Loki()
{
	characterLoki = NULL;
}

void Loki::Shoot()
{
    Sprite spBullet("img/characters/lokiFireball.png",3,0.1);
    float shootingAngle = (hState == MOVING_RIGHT or hState == STANDING_RIGHT) ? 0 : M_PI;
    Bullet* fireBall=new Bullet(box.Center().GetX(),box.Center().GetY(),shootingAngle,FIREBALL_SPEED,FIREBALL_DISTANCE,spBullet,"Loki",movementMap);
    Game::GetInstance().GetCurrentState().AddObject(fireBall); //add the bullet to the objectArray

    shootCooldown.Restart(); //restart the timer
    SetActionState(NONE);
}

void Loki::UpdateVerticalState()
{
	// If character center is below 9/10 of the barrier, then the character is suspended.
	if ( ((Barrier::barrier->GetCorner().GetY()+(Barrier::barrier->DIAMETER*9/10)) < box.Center().GetY())
			&& (box.Center().Distance(Thor::characterThor->box.Center()) >= Barrier::barrier->DIAMETER - Barrier::barrier->DRAG_TOLERANCE) )
	    barrierSuspended = true;
	else
	    barrierSuspended = false;

    if (appearance == LOKI)
    {
        if (vertical == 1 and vState == STANDING)
            SetVState(JUST_JUMPED);
        else if (vertical == 1 and (vState == FALLING or vState == JUMPING) and actionState == NONE and !cannotTransform)
            SetAppearance(EAGLE);
    }
    else if (appearance == EAGLE)
    {
        if (vertical == 1 and flappedWings < TIMES_FLAPS_WINGS){
            SetVState(JUST_JUMPED);
            flappedWings++;
        }
        else if (vertical == -1)
            SetAppearance(LOKI);
    }
    transformTime.Update(dt);
    cannotTransform = false;
}

/**
 * Should change the MovementState in case loki transformed into an animal
 */
bool Loki::IndividualMovStateSelection()
{
    if (appearance == EAGLE)
        ChangeMovementState("Eagle");
    else return(false);
    return(true);
}

/**
 * Calls the right action Loki must do, depending on the situation
 */
void Loki::Act()
{
    shootCooldown.Update(dt);
    if (!actionButton) return;
    if (appearance == LOKI)
    {
        if (canPressSwitch)
            pressSwitch = true;
        if(ItemFlags::fireBall and shootCooldown.Get() >= COOLDOWN and vState == STANDING)
            Shoot();
    }
    actionButton = false;
}

void Loki::UpdatesStateOnTheFall()
{
    if (vState == JUST_JUMPED)
        SetVState(JUMPING);
    if (vState == STANDING)
    {
        SetAppearance(LOKI);
        flappedWings = 0;
    }
    else if (speed.GetY()>0) SetVState(FALLING);
}

bool Loki::Is(std::string type)
{
	return type == "Loki" ? true : false;
}

/**
 * Updates the sprite based on the state of the character
 */
void Loki::UpdateSprite()
{
    if (appearance == LOKI)
    {
        if (vState == STANDING)
        {
            if (hState == MOVING_RIGHT or hState == MOVING_LEFT)
                prevHState != hState ? ChangeSp("walkSp","img/characters/loki_walk.png",7) : walkSp.Update(dt);
            else if (hState == STANDING_RIGHT or hState == STANDING_LEFT)
                ChangeSp("characterSp","img/characters/loki.png",1);
        }
        else if (actionState == CLIMBING)
        {
            if (prevActionState != CLIMBING)
                ChangeSp("climbSp","img/characters/lokiStairs.png",3);
            else if (vertical != 0) climbSp.Update(dt);
        }
        else if (actionState == CLIMBING_GATE)
        {
            if (prevActionState != CLIMBING_GATE)
                ChangeSp("climbSp","img/characters/lokiStairs.png",3);
            else if (vertical != 0 or horizontal != 0)
            	climbSp.Update(dt);
        }
        else if (vState == FALLING)
            ChangeSp("jumpSp","img/characters/lokiJump.png",4,4,false);
        else if (vState == JUMPING)
        {
            if (prevVState == JUST_JUMPED)
                ChangeSp("jumpSp","img/characters/lokiJump.png",4,1,false);
            else
                jumpSp.Update(dt);
        }

        shouldRender = true;
    }
    else if (appearance == EAGLE)
    {
        if (prevAppearance == LOKI)
        {
            ChangeSp("jumpSp","img/characters/eagleFlight.png",10);
            //adds a smoke to the screen
            Sprite smoke("img/characters/smoke.png", 11, 0.1);
            StillAnimation *sa = new StillAnimation(box.Center().GetX(),box.Center().GetY(),rotation,smoke,1,true);
            Game::GetInstance().GetCurrentState().AddObject(sa);
        }
        else if (transformTime.Get() > TRANSFORM_COOLDOWN)
            jumpSp.Update(dt);

        transformTime.Get() < TRANSFORM_COOLDOWN ? shouldRender = false : shouldRender = true;
    }
    prevAppearance = appearance;
}

/**
 * Changes the appearance from loki<-->eagle.
 * The eagle will not be shown when it transforms, as to seem it is behind a smoke cloud
 */
void Loki::SetAppearance(TransformState appearance)
{
    if (appearance == EAGLE and !ItemFlags::eagle) return;
    prevAppearance = this->appearance;
    this->appearance = appearance;
    if (appearance == EAGLE)
        transformTime.Restart();
}
