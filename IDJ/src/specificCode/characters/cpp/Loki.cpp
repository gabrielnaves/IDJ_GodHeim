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
	horizontal = 0;
	vertical = 0;
}

Loki::~Loki()
{
	characterLoki = NULL;
}

void Loki::Input()
{
	InputManager &input = InputManager::GetInstance();
	//sets the directions in which the camera must move
	if (input.KeyPress(SDLK_d) || input.IsKeyDown(SDLK_d))
		horizontal+=1;
	if (input.KeyPress(SDLK_a) || input.IsKeyDown(SDLK_a))
		horizontal-=1;
	if (input.KeyPress(SDLK_w) || input.IsKeyDown(SDLK_w))
		vertical-=1;
	if (input.KeyPress(SDLK_s) || input.IsKeyDown(SDLK_s))
		vertical+=1;
	if (input.KeyPress(SDLK_e)) return; //TODO: action button
}


void Loki::Move(float dt)
{
	if (vertical!=0) Jump(dt);
	if (horizontal!=0) Walk(dt);
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
