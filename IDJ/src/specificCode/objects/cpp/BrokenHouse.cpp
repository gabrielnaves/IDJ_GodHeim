/*
 * BrokenHouse.cpp
 *
 *  Created on: Jun 8, 2014
 *      Author: icaro
 */

#include "../include/BrokenHouse.h"

BrokenHouse::BrokenHouse() {
   frontHouseSp.Open("img/primeira fase/casa-2.png");
   box.Set(510,297,backHouseSp.GetWidth(),backHouseSp.GetHeight());
}

void BrokenHouse::RenderFront()
{
    frontHouseSp.Render(box.GetX()-Camera::pos.GetX(), box.GetY()-Camera::pos.GetY());
}

void BrokenHouse::RenderBack()
{
    backHouseSp.Render(box.GetX()-Camera::pos.GetX(), box.GetY()-Camera::pos.GetY());
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
