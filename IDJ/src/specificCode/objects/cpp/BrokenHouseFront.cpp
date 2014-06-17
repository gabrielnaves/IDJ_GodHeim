/*
 * BrokenHouse.cpp
 *
 *  Created on: Jun 8, 2014
 *      Author: icaro
 */

#include "../include/BrokenHouseFront.h"

BrokenHouseFront::BrokenHouseFront(float x, float y) {
   frontHouseSp.Open("img/objects/houseFront.png");
   housePos.Set(x, y);
   box.Set(x+52, y+11, 117, 56);
}

BrokenHouseFront::~BrokenHouseFront() {}

void BrokenHouseFront::Render()
{
    frontHouseSp.Render(housePos.GetX()-Camera::pos.GetX(), housePos.GetY()-Camera::pos.GetY());
}


void BrokenHouseFront::Update(float dt)
{
    Loki* loki = Loki::characterLoki;
    Thor* thor = Thor::characterThor;
    if (loki->box.Center().Distance(box.Center()) < 200 || thor->box.Center().Distance(box.Center()) < 200)
    {

    }
}

bool BrokenHouseFront::Is(std::string type)
{
    return(type == "BrokenHouse" ? true : false);
}
