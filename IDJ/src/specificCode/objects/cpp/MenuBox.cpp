/*
 * MenuBox.cpp
 *
 *  Created on: Jun 9, 2014
 *      Author: Gabriel Naves
 */

#include "../include/MenuBox.h"

MenuBox::MenuBox(float x, float y, std::string spFile1, std::string spFile2, std::string type)
{
    sp1.Open(spFile1);
    sp2.Open(spFile2);
    box.Set(x, y, sp1.GetWidth(), sp1.GetHeight());
    click = false;
    isMouseInside = false;
    this->type = type;
    clickSound.Open("audio/SOUNDTRACK MODE/Menu/Click.ogg");
    thunderSound.Open("audio/SOUNDTRACK MODE/Menu/Trovao.ogg");
}

void MenuBox::Update(float dt)
{
    if (InputManager::GetInstance().IsMouseInside(box) && isMouseInside == false)
    {
        isMouseInside = true;
        clickSound.Play(0);
    }
    else if (!InputManager::GetInstance().IsMouseInside(box))
        isMouseInside = false;

    if (isMouseInside && InputManager::GetInstance().MousePress(LEFT_MOUSE_BUTTON))
    {
        click = true;
        thunderSound.Play(0);
    }
}

void MenuBox::Render()
{
    if (isMouseInside) sp2.Render(box.GetX(), box.GetY());
    else sp1.Render(box.GetX(), box.GetY());
}

void MenuBox::NotifyCollision(GameObject& other) {}

bool MenuBox::IsDead()
{
    return click;
}

bool MenuBox::Is(std::string type)
{
    return type == this->type ? true : false;
}
