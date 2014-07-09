/*
 * Portal.cpp
 *
 *  Created on: Jul 8, 2014
 *      Author: Gabriel Naves
 */

#include "../include/Portal.h"

Portal::Portal(float x, float y) : inactiveSp("img/level2/portal.png"),
                                   activeSp("img/level2/portalas.png", 5, 0.1, true)
{
    box.Set(x, y, inactiveSp.GetWidth(), inactiveSp.GetHeight());
    rotation = 0;
    active = false;
}

void Portal::Update(float dt)
{
    if (ItemFlags::redPotion) active = true;
    if (active) activeSp.Update(dt);
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

}

bool Portal::Is(std::string type)
{
    return type == "Portal" ? true : false;
}
