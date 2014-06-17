/*
 * Plants.cpp
 *
 *  Created on: Jun 9, 2014
 *      Author: icaro
 */

#include "../include/Plants.h"

Plants::Plants(std::string plant, int x, int y) {
    plantSp.Open(plant);
    box.Set(x,y,plantSp.GetWidth(),plantSp.GetHeight());
}

Plants::~Plants() {
}

void Plants::Update(float dt) {}

void Plants::Render()
{
    plantSp.Render(box.GetX()-Camera::pos.GetX(), box.GetY()-Camera::pos.GetY());
}

bool Plants::Is(std::string type)
{
    return(type == "Plants" ? true : false);
}
