/*
 * Character.cpp
 *
 *  Created on: May 23, 2014
 *      Author: icaro
 */

#include "../include/Character.h"
#include "../../Barrier.h"

bool Character::HasReachedBarrier(float dx, float dy)
{
	float x_distance = box.GetCenter().GetX() + dx - Barrier::barrier->box.GetCenter().GetX();
	float y_distance = box.GetCenter().GetY() + dy - Barrier::barrier->box.GetCenter().GetY();
	float distance = sqrt(pow(x_distance,2)+pow(y_distance,2));
	return (distance >= Barrier::barrier->DIAMETER/2 ? true : false);
}

void Character::Walk(float dt)
{
	speed.SetPoint(VEL*horizontal,0);
	float dx = speed.GetX()*dt;
	if (HasReachedBarrier(dx,0))
		dx = 0;
	box.MoveRect(dx,0);
	horizontal = 0;
}

void Character::Jump(float dt)
{
	float dy = VEL*vertical*dt;
	if (HasReachedBarrier(0,dy))
		dy = 0;
	box.MoveRect(0,dy);
	vertical = 0;
}

void Character::NotifyCollision(GameObject& other)
{

}

bool Character::IsDead()
{
	return hp <= 0 ? true : false;
}
