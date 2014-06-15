/*
 * Cursor.cpp
 *
 *  Created on: Jun 13, 2014
 *      Author: arthur
 */

#include "../include/Cursor.h"

Cursor::Cursor(): sp("img/menu/mouse.png")
{
	box.Set(InputManager::GetInstance().GetMouseX()-sp.GetWidth()/2 -15,
			InputManager::GetInstance().GetMouseY()-sp.GetHeight()/2 +15, sp.GetWidth(), sp.GetHeight());
	rotation = 45;
	click = false;
}

void Cursor::Update(float dt)
{
	if (InputManager::GetInstance().MousePress(1))	click = true;
	box.SetPoint(InputManager::GetInstance().GetMouseX()-sp.GetWidth()/2 -15,
				 InputManager::GetInstance().GetMouseY()-sp.GetHeight()/2 +15);

	if (click)
	{
		timer.Update(dt);
		rotation = 90;
		if ((timer.Get() >= CLICK_TIME) && (!InputManager::GetInstance().IsMouseDown(1)))
		{
			timer.Restart();
			rotation = 45;
			click = false;
		}
	}
}

void Cursor::Render()
{
	sp.Render(box.GetX()-Camera::pos.GetX(), box.GetY()-Camera::pos.GetY(), rotation);
}

void Cursor::NotifyCollision(GameObject& other)
{
}

bool Cursor::IsDead()
{
	return false;
}

bool Cursor::Is(std::string type)
{
	return type == "Cursor" ? true : false;
}
