/*
 * Bridge.cpp
 *
 *  Created on: Jun 9, 2014
 *      Author: Gabriel Naves
 */

#include "../include/Bridge.h"

Bridge::Bridge(float x, float y)
{
    bridgeSp.Open("img/primeira fase/ponte.png");
    box.Set(x, y, bridgeSp.GetWidth(), bridgeSp.GetHeight());
}

Bridge::~Bridge()
{
    // TODO Auto-generated destructor stub
}

void Bridge::Update(float dt)
{

}

void Bridge::Render()
{
    bridgeSp.Render(box.GetX()-Camera::pos.GetX(), box.GetY()-Camera::pos.GetY());
}

void Bridge::NotifyCollision(GameObject& other)
{

}

bool Bridge::IsDead()
{
    return false;
}

bool Bridge::Is(std::string type)
{
    return type == "Bridge" ? true : false;
}
