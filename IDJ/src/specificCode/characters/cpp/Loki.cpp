/*
 * Loki.cpp
 *
 *  Created on: May 19, 2014
 *      Author: Gabriel Naves
 */

#include "../include/Loki.h"

Loki::Loki(float x, float y)
{
	hp = 100;
	rotation = 0;
	tempLoki.Open("img/tempLoki.jpg");
	box.SetRect(x-tempLoki.GetWidth()/2, y-tempLoki.GetHeight()/2, tempLoki.GetWidth(), tempLoki.GetHeight());
}

Loki::~Loki()
{
	// TODO Auto-generated destructor stub
}

void Loki::Update(float dt)
{
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
