/*
 * Portal.cpp
 *
 *  Created on: Jul 8, 2014
 *      Author: Gabriel Naves
 */

#include "../include/Portal.h"

bool Portal::endLevel2 = false;

Portal::Portal(float x, float y) : inactiveSp("img/level2/portal.png"),
                                   activeSp("img/level2/portalas.png", 5, 0.1, true)
{
    box.Set(x, y, inactiveSp.GetWidth(), inactiveSp.GetHeight());
    rotation = 0;
    active = end = false;
    thorColliding = lokiColliding = false;
}

void Portal::Update(float dt)
{
    if (!thorColliding or !lokiColliding)
        thorColliding = lokiColliding = false;
    if (ItemFlags::redPotion) active = true;
    if (active)
    {
        activeSp.Update(dt);
        if (thorColliding and lokiColliding)
            end = true;
    }
    if (end) endTimer.Update(dt);
    if (endTimer.Get() >= 1)
        endLevel2 = true;
}

void Portal::Render()
{
    if (!active)
        inactiveSp.Render(box.GetX()-Camera::pos.GetX(), box.GetY()-Camera::pos.GetY());
    else
        activeSp.Render(box.GetX()-Camera::pos.GetX(), box.GetY()-Camera::pos.GetY());
}

void Portal::NotifyCollision(GameObject& other)
{
    if (other.Is("Loki")) lokiColliding = true;
    if (other.Is("Thor")) thorColliding = true;
}

bool Portal::Is(std::string type)
{
    return type == "Portal" ? true : false;
}
