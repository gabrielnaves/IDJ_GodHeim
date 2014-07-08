/*
 * Item.cpp
 *
 *  Created on: Jun 15, 2014
 *      Author: icaro
 */

#include "../include/Item.h"

Item::Item(int x, int y, std::string imageAdress, std::string name)
{
    SetConstructor(x,y,imageAdress,name,true,true,false,0);
}

Item::Item(int x, int y, std::string imageAdress, std::string name, bool thorCatches, bool lokiCatches)
{
    SetConstructor(x,y,imageAdress,name,thorCatches,lokiCatches,false,0);
}

Item::Item(int x, int y, std::string imageAdress, std::string name, bool thorCatches, bool lokiCatches, bool delayed, float delay)
{
    SetConstructor(x,y,imageAdress,name,thorCatches,lokiCatches,delayed,delay);
}

void Item::SetConstructor(int x, int y, std::string imageAdress, std::string name, bool thorCatches, bool lokiCatches, bool delayed, float delay)
{
    itemSp.Open(imageAdress);
    box.Set(x-itemSp.GetWidth()/2,y-itemSp.GetHeight()/2,itemSp.GetWidth(),itemSp.GetHeight());
    this->name = name;
    hasItem = false;
    angle = 0;
    initialY = box.GetY();
    disappear = false;
    this->delayed = delayed;
    delayTime = delay;
    this->thorCatches = thorCatches;
    this->lokiCatches = lokiCatches;
    hover = true;
}

Item::~Item() {}

void Item::SetHover(bool hover)
{
	this->hover = hover;
}

void Item::Update(float dt)
{
    if (delayed)
    {
        delay.Update(dt);
        if (delay.Get() >= delayTime) delayed = false;
    }
    else Hover(dt);
}

void Item::Render()
{
    if (!delayed)
        itemSp.Render(box.GetX()-Camera::pos.GetX(), box.GetY()-Camera::pos.GetY());
}

/**
 * If the right item collides with the right character, it will
 * disappear and set the corresponding flag on the character.
 */
void Item::NotifyCollision(GameObject& other)
{
    if (!delayed)
    {
        if (other.Is("Thor"))
            if (thorCatches) disappear = true;
        if (other.Is("Loki"))
            if (lokiCatches) disappear = true;
    }
    if (disappear)
        ItemFlags::ChangeFlag(name, true); //sets the corresponding itemflag to true, so the characters know it was caught
}

/**
 * Returns true for both its general type (Item) and
 * its specific item name (name).
 */
bool Item::Is(std::string type)
{
    if (type == "Item") return true;
    if (type == name) return true;
    return false;
}

bool Item::IsDead()
{
    return disappear ? true : false;
}

void Item::Hover(float dt)
{
	if (!hover) return;
    angle = angle + dt * 3;
    if (angle >= 2*M_PI) angle -= 2*M_PI;
    box.Set(box.GetX(), initialY + cos(angle) * 5, box.GetW(), box.GetH());
}
