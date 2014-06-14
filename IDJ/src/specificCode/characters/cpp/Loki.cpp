/*
 * Loki.cpp
 *
 *  Created on: May 19, 2014
 *      Author: Gabriel Naves
 *              Icaro Mota
 */

#include "../include/Loki.h"

Loki* Loki::characterLoki;

Loki::Loki(float x, float y, MovementMap& movMap) : Character(movMap,"img/characters/loki_walk.png",8,0.1,"img/characters/thor_jump.png",4,0.1)
{
	characterSp.Open("img/characters/loki.png");
	box.Set(x-characterSp.GetWidth()/2, y-characterSp.GetHeight()/2, characterSp.GetWidth(), characterSp.GetHeight());
	characterLoki = this;
	appearance = LOKI;
	flappedWings = 0;
	TIMES_FLAPS_WINGS = 1;
    actionState = NONE;
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
    actionState = NONE;
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
}

void Loki::UpdateVerticalState()
{
    if (appearance == LOKI)
    {
        if (vertical == 1 and vState == STANDING)
            SetVState(JUST_JUMPED);
        else if (vertical == 1 and vState == FALLING and actionState == NONE)
            appearance = EAGLE;
    }
    else if (appearance == EAGLE)
    {
        if (vertical == 1 and flappedWings < TIMES_FLAPS_WINGS){
            SetVState(JUST_JUMPED);
            flappedWings++;
        }
        else if (vertical == -1)
            appearance = LOKI;
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

    //If the character colided with the upper limit of the barrier, makes sure it will not keep on jumping
    if ((vState == JUMPING or vState == JUST_JUMPED) and (Thor::characterThor->box.GetY() - box.GetY() >= Barrier::barrier->DIAMETER))
        speed.Set(speed.GetX(),0); //sets the Y speed to 0 when it hits the upper limmit of the barrier
}

void Loki::ReleasesStairs()
{
    actionState = NONE;
    SetVState(FALLING);
}

void Loki::HoldStairs()
{
    actionState = CLIMBING;
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
        appearance = LOKI;
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
    if (actionState == CLIMBING and !canHoldStairs) actionState = NONE;
    Move(dt);
    UpdatesStateOnTheFall();
    UpdateSprite(dt);
    CheckMovementLimits();
    UpdatePrevState();
}

void Loki::NotifyCollision(GameObject& other)
{
    if (other.Is("Stairs"))
    {
        if ((box.GetX() >= box.GetX()) and ((box.GetX()+box.GetW()) <= (other.box.GetX()+other.box.GetW())))
        {
                //if the character is close enough in the y axis to go down the stairs
                if (box.GetY()<=(other.box.GetY()-box.GetH()+50) and box.GetY()>=(other.box.GetY()-box.GetH()-2) and actionState != CLIMBING)
                {
                    box.SetPoint(box.GetX(),other.box.GetPoint().GetY()-box.GetH()); //corrects bugs
                    SetVState(STANDING);
                }
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
            if (hState == MOVING_RIGHT)
                prevHState != MOVING_RIGHT ? walkSp.Open("img/characters/loki_walk.png") : walkSp.Update(dt);
            else if (hState == MOVING_LEFT)
                prevHState != MOVING_LEFT ? walkSp.Open("img/characters/loki_walk.png") : walkSp.Update(dt);
            else if (hState == STANDING_RIGHT)
                characterSp.Open("img/characters/loki.png");
            else if (hState == STANDING_LEFT)
                characterSp.Open("img/characters/loki.png");
        }
        else if (actionState == CLIMBING)
            characterSp.Open("img/characters/loki.png");
        else if (vState == FALLING)
        {
            jumpSp.SetFrameCount(4);
//            jumpSp.SetFrame(4);
            jumpSp.Open("img/characters/thor_jump.png");
        }
        else if (vState == JUMPING)
        {
            jumpSp.SetFrame(1);
            jumpSp.SetFrameCount(4);
            prevVState == JUST_JUMPED ? jumpSp.Open("img/characters/thor_jump.png") : jumpSp.Update(dt);
        }
    }
    else if (appearance == EAGLE)
    {
        jumpSp.SetFrameCount(1);
        jumpSp.SetFrame(1);
        jumpSp.Open("img/characters/aguia.png");
    }
}
