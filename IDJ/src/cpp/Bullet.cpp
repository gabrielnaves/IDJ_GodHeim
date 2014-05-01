/*
 * Bullet.cpp
 *
 *  Created on: Apr 26, 2014
 *      Author: Gabriel Naves
 */

#include "../include/Bullet.h"

Bullet::Bullet(float x, float y, float angle, float speed, float maxDistance, Sprite sprite)
{
    sp = sprite;
    this->speed.SetPoint(speed * cos(angle), speed * sin(angle));
    distanceLeft = maxDistance;
    rotation = angle * 360 / (2*M_PI);
    box.SetRect(x-sp.GetWidth()/2, y-sp.GetHeight()/2, sp.GetWidth(), sp.GetHeight());
}

void Bullet::Update(float dt)
{
    sp.Update(dt);
    box.MoveRect(speed.GetX()*dt, speed.GetY()*dt);
    distanceLeft = distanceLeft - sqrt(pow(speed.GetX()*dt, 2) + pow(speed.GetY()*dt, 2));
}

void Bullet::Render()
{
    sp.Render(box.GetX() - Camera::pos.GetX(), box.GetY() - Camera::pos.GetY(), rotation);
}

bool Bullet::IsDead()
{
    return distanceLeft <= 0 ? true : false;
}
