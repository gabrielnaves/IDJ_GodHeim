/*
 * LavaCircle.cpp
 *
 *  Created on: Jun 17, 2014
 *      Author: Gabriel Naves
 */

#include "../include/LavaCircle.h"

LavaCircle::LavaCircle(float x, float y) : sp("img/level2/lavaCircle.png")
{
    box.Set(x-sp.GetWidth()/2, y-sp.GetHeight()/2, sp.GetWidth(), sp.GetHeight());
    rotation = 0;
}

LavaCircle::~LavaCircle()
{
    // TODO Auto-generated destructor stub
}

void LavaCircle::Update(float dt)
{
    rotation = rotation + 10*dt;
    if (rotation >= 360) rotation = rotation - 360;
}

void LavaCircle::Render()
{
    sp.Render(box.GetX()-Camera::pos.GetX(), box.GetY()-Camera::pos.GetY(), rotation);
}

bool LavaCircle::Is(std::string type)
{
    return type == "LavaCircle" ? true : false;
}
