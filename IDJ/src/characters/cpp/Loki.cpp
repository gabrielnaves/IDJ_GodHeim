/*
 * Loki.cpp
 *
 *  Created on: May 19, 2014
 *      Author: Gabriel Naves
 */

#include "../include/Loki.h"

Loki::Loki()
{
	hp = 100;
	rotation = 0;
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
