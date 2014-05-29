/*
 * Loki.cpp
 *
 *  Created on: May 19, 2014
 *      Author: Gabriel Naves
 *              Icaro Mota
 */

#include "../include/Loki.h"

Loki* Loki::characterLoki;

Loki::Loki(float x, float y, MovementMap movMap) : Character(movMap)
{
	hp = 100;
	rotation = 0;
	tempCharacterSp.Open("img/Characters/tempLoki.jpg");
	box.Set(x-tempCharacterSp.GetWidth()/2, y-tempCharacterSp.GetHeight()/2, tempCharacterSp.GetWidth(), tempCharacterSp.GetHeight());
	characterLoki = this;
	appearance = LOKI;
	flappedWings = 0;
	TIMES_FLAPS_WINGS = 1;
}

Loki::~Loki()
{
	characterLoki = NULL;
}

void Loki::Input()
{
    int horizontal = 0;
    InputManager &input = InputManager::GetInstance();
    //Gets the inputs for moving horizontally
    if (input.KeyPress(SDLK_d) || input.IsKeyDown(SDLK_d))
        horizontal += 1;
    if (input.KeyPress(SDLK_a) || input.IsKeyDown(SDLK_a))
        horizontal -= 1;
    UpdateHorizontalState(horizontal);
    //Gets the inputs for moving vertically
    if (appearance == LOKI)
    {
        if (input.KeyPress(SDLK_w) and vState == STANDING)
            vState = JUST_JUMPED;
        else if (input.KeyPress(SDLK_w) and vState == FALLING)
            appearance = EAGLE;
    }
    else if (appearance == EAGLE)
    {
        if (input.KeyPress(SDLK_w) and flappedWings < TIMES_FLAPS_WINGS)
            vState = JUST_JUMPED;
        else if (input.KeyPress(SDLK_s))
            appearance = LOKI;
    }
    if (input.KeyPress(SDLK_e))
    {
        actionButton = true;
    }
}

void Loki::Shoot()
{
    Sprite spBullet("img/Characters/minionbullet.png",3,0.1);
    float shootingAngle = (hState == MOVING_RIGHT or hState == STANDING_RIGHT) ? 0 : M_PI;
    Bullet* fireBall=new Bullet(box.Center().GetX(),box.Center().GetY(),shootingAngle,FIREBALL_SPEED,FIREBALL_DISTANCE,spBullet,"Loki");
    Game::GetInstance().GetCurrentState().AddObject(fireBall); //add the bullet to the objectArray
}

void Loki::UpdateEagleSpeed(float dt)
{
    if (vState == JUST_JUMPED)
        speed.Set(speed.GetX(),EAGLE_JUMP_SPEED);
    else if (vState == FALLING or vState == JUMPING) //unnecessary if. it is hero only in case more vStates are implemented
    {
        if (Barrier::barrier->CollidesAbove(this)) //TODO: STILL NOT WORKING
            speed = speed + Point(speed.GetX(),GRAVITY*dt);
        else
            speed = speed + Point(speed.GetX(),(GRAVITY - EAGLE_AIR_RESISTANCE)*dt);
    }

    if (hState == STANDING_LEFT or hState == STANDING_RIGHT) speed.Set(0,speed.GetY());
    else if (hState == MOVING_RIGHT) speed.Set(VEL,speed.GetY());
    else if (hState == MOVING_LEFT) speed.Set(-VEL,speed.GetY());

    if (speed.GetY() >= MAX_FALLING_SPEED_EAGLE) speed.Set(speed.GetX(), MAX_FALLING_SPEED_EAGLE);
}

void Loki::UpdateVerticalState()
{
    if ((vState == JUMPING or vState == JUST_JUMPED) and (Thor::characterThor->box.GetY() - box.GetY() >= Barrier::barrier->DIAMETER))
        speed.Set(speed.GetX(),0); //sets the Y speed to 0 when it hits the upper limmit of the barrier
    if (vState == JUST_JUMPED)
    {
        vState = JUMPING;
        if (appearance == EAGLE) flappedWings++;
    }
    if (speed.GetY()>0) vState = FALLING;
}

void Loki::Move(float dt)
{
    if (appearance == LOKI) UpdateSpeed(dt);
    if (appearance == EAGLE) UpdateEagleSpeed(dt);
    UpdateVerticalState();

    box.MoveRect(speed.GetX()*dt,speed.GetY()*dt);
    Barrier::barrier->CheckCollision(this);
}

void Loki::Action()
{
    if (appearance == LOKI and not (vState == JUMPING or vState == FALLING or vState == JUST_JUMPED))
        Shoot();
    actionButton = false;
}

void Loki::Update(float dt)
{
    Input();
    UpdateSprite();
    Move(dt);
    if (actionButton) Action();
    CheckMovementLimits();
    if (vState == STANDING)
    {
        appearance = LOKI;
        flappedWings = 0;
    }
}

void Loki::Render()
{
	tempCharacterSp.Render(box.GetX()-Camera::pos.GetX(), box.GetY()-Camera::pos.GetY());
}

void Loki::NotifyCollision(GameObject& other)
{

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
        if (hState == MOVING_RIGHT)
            tempCharacterSp.Open("img/Characters/tempLokiInvertido.png");
        if (hState == STANDING_RIGHT)
            tempCharacterSp.Open("img/Characters/tempLokiInvertido.png");
        if (hState == MOVING_LEFT)
            tempCharacterSp.Open("img/Characters/tempLoki.jpg");
        if (hState == STANDING_LEFT)
            tempCharacterSp.Open("img/Characters/tempLoki.jpg");
    }
    else if (appearance == EAGLE)
    {
        tempCharacterSp.Open("img/Characters/aguia.png");
    }
}
