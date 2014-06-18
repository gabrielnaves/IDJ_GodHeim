/*
 * Item.cpp
 *
 *  Created on: Jun 15, 2014
 *      Author: icaro
 */

#include "../include/Item.h"

Item::Item(int x, int y, std::string imageAdress, std::string name)
{
    itemSp.Open(imageAdress);
    box.Set(x,y,itemSp.GetWidth(),itemSp.GetHeight());
    this->name = name;
    hasItem = false;
}

Item::~Item() {}

void Item::Update(float dt)
{
}

void Item::Render()
{
    itemSp.Render(box.GetX()-Camera::pos.GetX(), box.GetY()-Camera::pos.GetY());
}

bool Item::Is(std::string type)
{
    return (type == "Item" ? true:false);
}

bool Item::IsCalled(std::string name)
{
    return (this->name == name ? true : false);
}

bool Item::HasItem() { return(hasItem); }
