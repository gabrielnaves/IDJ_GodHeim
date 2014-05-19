/*
 * StillAnimation.cpp
 *
 *  Created on: May 2, 2014
 *      Author: Gabriel Naves
 */

#include "../include/StillAnimation.h"

StillAnimation::StillAnimation(float x, float y, float rotation, Sprite sprite, float timeLimit, bool ends) : sp(sprite)
{
    box.SetRect(x-sp.GetWidth()/2, y-sp.GetHeight()/2, sp.GetWidth(), sp.GetHeight());
    this->rotation = rotation;
    this->timeLimit = timeLimit;
    oneTimeOnly = ends;
}

void StillAnimation::Update(float dt)
{
    sp.Update(dt);
    if (oneTimeOnly)
        endTimer.Update(dt);
}

void StillAnimation::Render()
{
    sp.Render(box.GetX()-Camera::pos.GetX(), box.GetY()- Camera::pos.GetY(), rotation);
}

bool StillAnimation::IsDead()
{
    return (oneTimeOnly && endTimer.Get() >= timeLimit) ? true : false;
}

bool StillAnimation::Is(std::string type)
{
    return type == "StillAnimation" ? true : false;
}

void StillAnimation::NotifyCollision(GameObject& other) {}
