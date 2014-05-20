/*
 * Thor.cpp
 *
 *  Created on: May 19, 2014
 *      Author: Gabriel Naves
 */

#include "../include/Thor.h"

Thor::Thor()
{
	hp = 100;
	rotation = 0;
}

Thor::~Thor()
{
	// TODO Auto-generated destructor stub
}

void Thor::Update(float dt)
{

}

void Thor::Render()
{

}

void Thor::NotifyCollision(GameObject& other)
{

}

bool Thor::IsDead()
{
	return hp <= 0 ? true : false;
}

bool Thor::Is(std::string type)
{
	return type == "Thor" ? true : false;
}
