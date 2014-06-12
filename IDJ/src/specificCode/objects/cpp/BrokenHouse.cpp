/*
 * BrokenHouse.cpp
 *
 *  Created on: Jun 8, 2014
 *      Author: icaro
 */

#include "../include/BrokenHouse.h"

BrokenHouse::BrokenHouse(float x, float y) {
   frontHouseSp.Open("img/objects/houseFront.png");
   backHouseSp.Open("img/objects/houseBack.png");
   housePos.Set(x, y);
   box.Set(x+52, y+11, 117, 56);
}

void BrokenHouse::RenderFront()
{
    frontHouseSp.Render(housePos.GetX()-Camera::pos.GetX(), housePos.GetY()-Camera::pos.GetY());
}

void BrokenHouse::RenderBack()
{
    backHouseSp.Render(housePos.GetX()-Camera::pos.GetX(), housePos.GetY()-Camera::pos.GetY());
}

BrokenHouse::~BrokenHouse() {}

void BrokenHouse::Update(float dt)
{
    Loki* loki = Loki::characterLoki;
    Thor* thor = Thor::characterThor;
    if (loki->box.Center().Distance(box.Center()) < 200 || thor->box.Center().Distance(box.Center()) < 200)
    {

    }
}

void BrokenHouse::Render() {}
void BrokenHouse::NotifyCollision(GameObject& other) {}

bool BrokenHouse::IsDead() { return(false); }

bool BrokenHouse::Is(std::string type)
{
    return(type == "BrokenHouse" ? true : false);
}
