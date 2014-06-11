/*
 * BrokenHouse.cpp
 *
 *  Created on: Jun 8, 2014
 *      Author: icaro
 */

#include "../include/BrokenHouse.h"

BrokenHouse::BrokenHouse(float x, float y) {
   frontHouseSp.Open("img/Objects/houseFront.png");
   backHouseSp.Open("img/Objects/houseBack.png");
   housePos.Set(x, y);
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
void BrokenHouse::Update(float dt) {}
void BrokenHouse::Render() {}
void BrokenHouse::NotifyCollision(GameObject& other) {}

bool BrokenHouse::IsDead() { return(false); }

bool BrokenHouse::Is(std::string type)
{
    return(type == "BrokenHouse" ? true : false);
}
