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
	tempCharacterSp.Open("img/tempLoki.jpg");
	box.SetRect(x-tempCharacterSp.GetWidth()/2, y-tempCharacterSp.GetHeight()/2, tempCharacterSp.GetWidth(), tempCharacterSp.GetHeight());
	characterLoki = this;
	horizontal = 0;
	vertical = 0;
	state = STANDING;
}

Loki::~Loki()
{
	characterLoki = NULL;
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
	tempCharacterSp.Render(box.GetX()-Camera::pos.GetX(), box.GetY()-Camera::pos.GetY());
}

void Loki::NotifyCollision(GameObject& other)
{

}

bool Loki::Is(std::string type)
{
	return type == "Loki" ? true : false;
}
