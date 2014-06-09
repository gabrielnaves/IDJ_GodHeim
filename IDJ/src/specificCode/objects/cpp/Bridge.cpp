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
    segment1.Set(x+10, y+110, x+65, y+70);
    segment2.Set(x+65, y+70, x+210, y+70);
    segment3.Set(x+210, y+70, x+260, y+110);
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
