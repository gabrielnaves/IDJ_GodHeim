/*
 * Character.cpp
 *
 *  Created on: May 23, 2014
 *      Author: icaro
 */

#include "../include/Character.h"
#include "../include/Barrier.h"

Character::Character(MovementMap movMap) : movementMap(movMap)
{
    hp = 100;
    vertical = horizontal = 0;
    state = STANDING;
}

bool Character::HasReachedBarrier(float dx, float dy)
{
    float x_distance = box.Center().GetX() + dx - Barrier::barrier->box.Center().GetX();
    float y_distance = box.Center().GetY() + dy - Barrier::barrier->box.Center().GetY();
    float distance = sqrt(pow(x_distance,2)+pow(y_distance,2));
    return (distance >= Barrier::barrier->DIAMETER/2 ? true : false);
}

void Character::UpdateSpeed(float dt)
{
	switch(state)
	{
		case STANDING:
			break;
		case JUMPING:
			break;
		case MOVING_RIGHT:
			break;
		case MOVING_LEFT:
			break;
	}
}

void Character::Walk(float dt)
{
    speed.Set(VEL*horizontal,0);
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
    return (Thor::characterThor == NULL or Loki::characterLoki == NULL);
}

void Character::CheckMovementLimits()
{
    // Checks the right limit
    if (!movementMap.IsZero(box.Center().GetX() + box.GetW()/2, box.Center().GetY()))
        box.MoveRect(movementMap.FindXDistance(box.Center().GetX() + box.GetW()/2, box.Center().GetY()),0);
    // Checks the left limit
    if (!movementMap.IsZero(box.Center().GetX() - box.GetW()/2, box.Center().GetY()))
        box.MoveRect(movementMap.FindXDistance(box.Center().GetX() - box.GetW()/2, box.Center().GetY()),0);
    // Checks the above limit
    if (!movementMap.IsZero(box.Center().GetX(), box.Center().GetY() - box.GetH()/2))
        box.MoveRect(0,movementMap.FindYDistance(box.Center().GetX(), box.Center().GetY() - box.GetH()/2));
    // Checks the lower limit
    if (!movementMap.IsZero(box.Center().GetX(), box.Center().GetY() + box.GetH()/2))
        box.MoveRect(0,movementMap.FindYDistance(box.Center().GetX(), box.Center().GetY() + box.GetH()/2));
}
