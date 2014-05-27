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
}

Loki::~Loki()
{
	characterLoki = NULL;
}

void Loki::Input()
{
    int horizontal = 0;
	InputManager &input = InputManager::GetInstance();
	//sets the directions in which the camera must move
	if (input.KeyPress(SDLK_d) || input.IsKeyDown(SDLK_d))
		horizontal += 1;
	if (input.KeyPress(SDLK_a) || input.IsKeyDown(SDLK_a))
		horizontal -= 1;
	UpdateHorizontalState(horizontal);

	if (input.KeyPress(SDLK_w) and vState == STANDING)
		vState = JUMPING;
	else if (input.KeyPress(SDLK_w) and vState == FALLING and appearance == LOKI)
	    appearance = EAGLE;
	else if (input.KeyPress(SDLK_w) and appearance == EAGLE)
	    vState = JUMPING;
}

void Loki::UpdateEagleSpeed(float dt)
{
    if (vState == JUMPING) speed.Set(speed.GetX(),JUMP_SPEED/2);
    else if (vState == FALLING) speed = speed + Point(speed.GetX(),(GRAVITY/4)*dt);

    if (hState == STANDING_LEFT or hState == STANDING_RIGHT) speed.Set(0,speed.GetY());
    else if (hState == MOVING_RIGHT) speed.Set(VEL,speed.GetY());
    else if (hState == MOVING_LEFT) speed.Set(-VEL,speed.GetY());

    if (speed.GetY() >= MAX_FALLING_SPEED) speed.Set(speed.GetX(), MAX_FALLING_SPEED);
}

void Loki::Move(float dt)
{
    if (appearance == LOKI) UpdateSpeed(dt);
	if (appearance == EAGLE) UpdateEagleSpeed(dt);
    if (vState == JUMPING) vState = FALLING;
	box.MoveRect(speed.GetX()*dt,speed.GetY()*dt);
	Barrier::barrier->CheckCollision(this);
}

void Loki::Update(float dt)
{
	Input();
	UpdateSprite();
	Move(dt);
	CheckMovementLimits();
	if (vState == STANDING) appearance = LOKI;
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

void Loki::UpdateSprite()
{
    if (hState == MOVING_RIGHT or hState == STANDING_RIGHT)
        tempCharacterSp.Open("img/Characters/tempLokiInvertido.png");
    else if (hState == MOVING_LEFT or hState == STANDING_LEFT)
        tempCharacterSp.Open("img/Characters/tempLoki.jpg");
}
