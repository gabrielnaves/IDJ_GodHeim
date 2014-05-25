/*
 * Loki.cpp
 *
 *  Created on: May 19, 2014
 *      Author: Gabriel Naves
 */

#include "../include/Loki.h"

Loki* Loki::characterLoki;

Loki::Loki(float x, float y, MovementMap movMap) : Character(movMap)
{
	hp = 100;
	rotation = 0;
	tempCharacterSp.Open("img/tempLoki.jpg");
	box.Set(x-tempCharacterSp.GetWidth()/2, y-tempCharacterSp.GetHeight()/2, tempCharacterSp.GetWidth(), tempCharacterSp.GetHeight());
	characterLoki = this;
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
}


void Loki::Move(float dt)
{
    UpdateSpeed(dt);
	if (vState == JUMPING) vState = FALLING;
	box.MoveRect(speed.GetX()*dt,speed.GetY()*dt);
}

void Loki::Update(float dt)
{
	Input();
	Move(dt);
	CheckMovementLimits();
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
