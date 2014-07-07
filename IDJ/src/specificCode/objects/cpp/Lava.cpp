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

void Lava::NotifyCollision(GameObject &other)
{
	if (other.box.GetX() > box.GetX()+box.GetW()+5 or other.box.GetX()+other.box.GetW() < box.GetX()-5) return;
	if (other.box.GetY()+other.box.GetH() < box.GetY()-10 or other.box.GetY() > box.GetY()+box.GetH()+10) return;
	if (other.Is("Thor")) Thor::characterThor->Kill();
	if (other.Is("Loki")) Loki::characterLoki->Kill();
}
