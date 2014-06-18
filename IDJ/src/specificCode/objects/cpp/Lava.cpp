/*
 * Lava.cpp
 *
 *  Created on: Jun 18, 2014
 *      Author: Gabriel Naves
 */

#include "../include/Lava.h"

Lava::Lava(float x, float y) : sp("img/level2/lava.png", 2, 0.3)
{
    box.Set(x, y, sp.GetWidth(), sp.GetHeight());
    rotation = 0;
}

Lava::~Lava()
{
}

void Lava::Update(float dt)
{
    sp.Update(dt);
}

void Lava::Render()
{
    sp.Render(box.GetX()-Camera::pos.GetX(), box.GetY()-Camera::pos.GetY());
}

bool Lava::Is(std::string type)
{
    return type == "Lava" ? true : false;
}
