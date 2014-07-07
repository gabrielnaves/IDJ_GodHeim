/*
 * Bullet.cpp
 *
 *  Created on: May 29, 2014
 *      Author: icaro
 */

#include "../include/Bullet.h"

/**
 * @Param angle must be in radians
 */
Bullet::Bullet(float x, float y, float angle, float speed, float maxDistance, Sprite sprite, std::string shooter, MovementMap movMap)
	: sp(sprite), movementMap(movMap)

{
	box.Set(x,y,sp.GetWidth(),sp.GetHeight());
	this->speed.Set(speed*cos(angle),speed*sin(angle));
	distanceLeft = maxDistance;
	rotation = angle*360/(2*M_PI);
	this->shooter = shooter;
}

void Bullet::Update(float dt)
{
	box.MoveRect(speed.GetX()*dt,speed.GetY()*dt);
	distanceLeft -= sqrt(pow(speed.GetX()*dt, 2) + pow(speed.GetY()*dt, 2));
	sp.Update(dt);
	CheckCollisionWithWall();
}

void Bullet::CheckCollisionWithWall()
{
    // Checks the right limit
    if (!movementMap.IsZero(box.Center().GetX() + box.GetW()/2, box.Center().GetY()))
        distanceLeft = 0;
    // Checks the left limit
    if (!movementMap.IsZero(box.Center().GetX() - box.GetW()/2, box.Center().GetY()))
    	distanceLeft = 0;
}

void Bullet::Render()
{
	sp.Render(box.GetX()-Camera::pos.GetX(),box.GetY()-Camera::pos.GetY(),rotation);
}

bool Bullet::IsDead()
{
	return(distanceLeft<=0 ? true:false);
}

bool Bullet::Is(std::string type)
{
	return (type == shooter+"Bullet" ? true : false);
}

void Bullet::NotifyCollision(GameObject &other)
{
    if (shooter == "Loki")
    {
        if (other.Is("Goat") or other.Is("Wolf") or other.Is("PlantBarrier"))
            distanceLeft = 0;
    }
}
