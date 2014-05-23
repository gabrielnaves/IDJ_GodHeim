/*
 * Loki.cpp
 *
 *  Created on: May 19, 2014
 *      Author: Gabriel Naves
 */

#include "../include/Loki.h"

Loki* Loki::characterLoki;

Loki::Loki(float x, float y)
{
	hp = 100;
	rotation = 0;
	tempLoki.Open("img/tempLoki.jpg");
	box.SetRect(x-tempLoki.GetWidth()/2, y-tempLoki.GetHeight()/2, tempLoki.GetWidth(), tempLoki.GetHeight());
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

bool Loki::HasReachedBarrier(float dx, float dy)
{
	float x_distance = box.GetCenter().GetX() + dx - Barrier::barrier->box.GetCenter().GetX();
	float y_distance = box.GetCenter().GetY() + dy - Barrier::barrier->box.GetCenter().GetY();
	float distance = sqrt(pow(x_distance,2)+pow(y_distance,2));
	return (distance >= Barrier::barrier->DIAMETER/2 ? true : false);
}

void Loki::Walk(float dt)
{
	float dx = vel*horizontal*dt;
	if (HasReachedBarrier(dx,0))
		dx = 0;
	box.MoveRect(dx,0);
	horizontal = 0;
}

void Loki::Jump(float dt)
{
	float dy = vel*vertical*dt;
	if (HasReachedBarrier(0,dy))
		dy = 0;
	box.MoveRect(0,dy);
	vertical = 0;
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
}

void Loki::Render()
{
	tempLoki.Render(box.GetX()-Camera::pos.GetX(), box.GetY()-Camera::pos.GetY());
}

void Loki::NotifyCollision(GameObject& other)
{

}

bool Loki::IsDead()
{
	return hp <= 0 ? true : false;
}

bool Loki::Is(std::string type)
{
	return type == "Loki" ? true : false;
}
