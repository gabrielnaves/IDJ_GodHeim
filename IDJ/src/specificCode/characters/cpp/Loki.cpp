/*
 * Loki.cpp
 *
 *  Created on: May 19, 2014
 *      Author: Gabriel Naves
 *              Icaro Mota
 */

#include "../include/Loki.h"

Loki* Loki::characterLoki;

Loki::Loki(float x, float y, MovementMap& movMap) :
        Character(movMap,"img/characters/loki_walk.png",8,0.1,"img/characters/lokiJump.png",4,0.1,"img/characters/lokiStairs.png",2,0.15)
{
	characterSp.Open("img/characters/loki.png");
	box.Set(x-characterSp.GetWidth()/2, y-characterSp.GetHeight()/2, characterSp.GetWidth(), characterSp.GetHeight());
	characterLoki = this;
	appearance = prevAppearance = LOKI;
	flappedWings = 0;
	TIMES_FLAPS_WINGS = 1;
}

Loki::~Loki()
{
	characterLoki = NULL;
}

void Loki::Input()
{
    horizontal = vertical = 0;
    InputManager &input = InputManager::GetInstance();
    //Gets the inputs for moving horizontally
    if (input.KeyPress(SDLK_d) || input.IsKeyDown(SDLK_d))
        horizontal += 1;
    if (input.KeyPress(SDLK_a) || input.IsKeyDown(SDLK_a))
        horizontal -= 1;
    //Gets the inputs for moving vertically
    if (input.KeyPress(SDLK_w))
        vertical += 1;
    else if (input.IsKeyDown(SDLK_w))
        vertical = 2;
    if (input.KeyPress(SDLK_s) || input.IsKeyDown(SDLK_s))
        vertical -= 1;
    //Action button
    if (input.KeyPress(SDLK_e))
        actionButton = true;
}

void Loki::Shoot()
{
    Sprite spBullet("img/characters/lokiFireball.png",3,0.1);
    float shootingAngle = (hState == MOVING_RIGHT or hState == STANDING_RIGHT) ? 0 : M_PI;
    Bullet* fireBall=new Bullet(box.Center().GetX(),box.Center().GetY(),shootingAngle,FIREBALL_SPEED,FIREBALL_DISTANCE,spBullet,"Loki");
    Game::GetInstance().GetCurrentState().AddObject(fireBall); //add the bullet to the objectArray

    shootCooldown.Restart(); //restart the timer
    SetActionState(NONE);
}

void Loki::UpdateEagleSpeed(float dt)
{
    if (vState == JUST_JUMPED)
        speed.Set(speed.GetX(),EAGLE_JUMP_SPEED);
    else if (vState == FALLING or vState == JUMPING) //unnecessary if. it is here only in case more vStates are implemented
        speed = speed + Point(speed.GetX(),(GRAVITY - EAGLE_AIR_RESISTANCE)*dt);

    if (hState == STANDING_LEFT or hState == STANDING_RIGHT) speed.Set(0,speed.GetY());
    else if (hState == MOVING_RIGHT) speed.Set(VEL,speed.GetY());
    else if (hState == MOVING_LEFT) speed.Set(-VEL,speed.GetY());

    if (speed.GetY() >= MAX_FALLING_SPEED_EAGLE) speed.Set(speed.GetX(), MAX_FALLING_SPEED_EAGLE);
    if (transformTime.Get() < TRANSFORM_COOLDOWN) speed.Set(0,0);
}

void Loki::UpdateVerticalState()
{
	// If character center is below 8/9 of the barrier, then the character is suspended.
	if ( ((Barrier::barrier->GetCorner().GetY()+(Barrier::barrier->DIAMETER*9/10)) < box.Center().GetY())
			&& (box.Center().Distance(Thor::characterThor->box.Center()) >= Barrier::barrier->DIAMETER - Barrier::barrier->DRAG_TOLERANCE) )
	    barrierSuspended = true;
	else
	    barrierSuspended = false;

    if (appearance == LOKI)
    {
        if (vertical == 1 and vState == STANDING)
            SetVState(JUST_JUMPED);
        else if (vertical == 1 and (vState == FALLING or vState == JUMPING) and actionState == NONE)
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
}

void Loki::Move(float dt)
{
    if (actionState == CLIMBING)
        Climb(dt);
    else if (appearance == LOKI) UpdateSpeed(dt);
    else if (appearance == EAGLE) UpdateEagleSpeed(dt);

    box.MoveRect(speed.GetX()*dt,speed.GetY()*dt);
    Barrier::barrier->CheckCollision(this);
}

void Loki::ReleasesStairs()
{
    SetActionState(NONE);
    SetVState(FALLING);
}

void Loki::HoldStairs()
{
    SetActionState(CLIMBING);
    box.SetPoint(box.GetPoint().GetX(),box.GetPoint().GetY()+1);
}

/**
 * Calls the right action Loki must do, depending on the situation
 */
void Loki::Act()
{
    if (appearance == LOKI)
    {
        if (actionState == CLIMBING)
            ReleasesStairs();
        else if (canHoldStairs)
            HoldStairs();
        else if(shootCooldown.Get() >= COOLDOWN and vState == STANDING)
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

void Loki::Update(float dt)
{
    Input();
    if (actionButton) Act();
    shootCooldown.Update(dt);
    UpdateState();
    transformTime.Update(dt);
    if (actionState == CLIMBING and !canHoldStairs) SetActionState(NONE);
    Move(dt);
    UpdatesStateOnTheFall();
    UpdateSprite(dt);
    CheckMovementLimits();
    UpdatePrevState();
    prevAppearance = appearance;
}

void Loki::NotifyCollision(GameObject& other)
{
    if (other.Is("Stairs"))
    {
        //if the character is close enough in the y axis to go down the stairs
        if (box.GetY()<=(other.box.GetY()-box.GetH()+50) and box.GetY()>=(other.box.GetY()-box.GetH()-2) and actionState != CLIMBING)
        {
            box.SetPoint(box.GetX(),other.box.GetPoint().GetY()-box.GetH()); //corrects bugs
            SetVState(STANDING);
        }
    }
    if (other.Is("Spikes"))
        hp -= HP/20;
}

bool Loki::Is(std::string type)
{
	return type == "Loki" ? true : false;
}

/**
 * Updates the sprite based on the state of the character
 */
void Loki::UpdateSprite(float dt)
{
    if (appearance == LOKI)
    {
        if (vState == STANDING)
        {
            if (hState == MOVING_RIGHT or hState == MOVING_LEFT)
                prevHState != hState ? ChangeSp("walkSp","img/characters/loki_walk.png",8) : walkSp.Update(dt);
            else if (hState == STANDING_RIGHT or hState == STANDING_LEFT)
                ChangeSp("characterSp","img/characters/loki.png",1);
        }
        else if (actionState == CLIMBING)
        {
            if (prevActionState != CLIMBING)
                ChangeSp("climbSp","img/characters/lokiStairs.png",2);
            else if (vertical != 0) climbSp.Update(dt);
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
}

/**
 * Changes the appearance from loki<-->eagle.
 * The eagle will not be shown when it transforms, as to seem it is behind a smoke cloud
 */
void Loki::SetAppearance(TransformState appearance)
{
    prevAppearance = this->appearance;
    this->appearance = appearance;
    if (appearance == EAGLE)
        transformTime.Restart();
}
