/*
 * BrokenHouseBack.cpp
 *
 *  Created on: Jun 17, 2014
 *      Author: Gabriel Naves
 */

#include "../include/BrokenHouseBack.h"

BrokenHouseBack::BrokenHouseBack(float x, float y)
{
    sp.Open("img/objects/houseBack.png");
    box.Set(x, y, sp.GetWidth(), sp.GetHeight());
}

BrokenHouseBack::~BrokenHouseBack() {}

void BrokenHouseBack::Update(float dt) {}

void BrokenHouseBack::Render()
{
    sp.Render(box.GetX()-Camera::pos.GetX(), box.GetY()-Camera::pos.GetY());
}

bool BrokenHouseBack::Is(std::string type)
{
    return type == "BrokenHouseBack" ? true : false;
}
