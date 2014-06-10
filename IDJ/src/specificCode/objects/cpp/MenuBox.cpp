/*
 * MenuBox.cpp
 *
 *  Created on: Jun 9, 2014
 *      Author: Gabriel Naves
 */

#include "../include/MenuBox.h"

MenuBox::MenuBox(float x, float y, Sprite sprite1, Sprite sprite2) : sp1(sprite1), sp2(sprite2)
{
    isMouseInside = false;
    box.Set(x, y, sprite1.GetWidth(), sprite1.GetHeight());
}

MenuBox::~MenuBox()
{
    // TODO Auto-generated destructor stub
}

void MenuBox::Update(float dt)
{
    if (InputManager::GetInstance().IsMouseInside(box))
        isMouseInside = true;
    else isMouseInside = false;
}

void MenuBox::Render()
{
    if (!isMouseInside) sp1.Render(box.GetX(), box.GetY());
    else sp2.Render(box.GetX(), box.GetY());
}

void MenuBox::NotifyCollision(GameObject& other) {}

bool MenuBox::IsDead()
{
    return false;
}

bool MenuBox::Is(std::string type)
{
    return type == "MenuBox" ? true : false;
}
