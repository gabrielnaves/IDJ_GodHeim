/*
 * ArrowButton.cpp
 *
 *  Created on: Jul 8, 2014
 *      Author: arthur
 */

#include "../include/ArrowButton.h"


ArrowButton::ArrowButton(float x, float y, bool increase, OptionBox* father)
{
	sp.Open("img/menu/seta.png");
	spClick.Open("img/menu/seta2.png");
	box.Set(x, y, sp.GetWidth(), sp.GetHeight());
	click = false;
	isMouseInside = false;
	this->increase = increase;
	this->father = father;
	clickSound.Open("audio/SOUNDTRACK MODE/Menu/Click.ogg");
}

void ArrowButton::Update(float dt)
{
	if (InputManager::GetInstance().IsMouseInside(box) && isMouseInside == false)
	{
		isMouseInside = true;
	}
	else if (!InputManager::GetInstance().IsMouseInside(box))
		isMouseInside = false;

	if (isMouseInside && InputManager::GetInstance().MousePress(LEFT_MOUSE_BUTTON))
	{
		click = true;
		Activate();
	}
}

void ArrowButton::Render()
{
	if (increase)
	{
		if (isMouseInside) spClick.Render(box.GetX(), box.GetY(), 0, SDL_FLIP_HORIZONTAL);
		else sp.Render(box.GetX(), box.GetY(), 0, SDL_FLIP_HORIZONTAL);
	}
	else
	{
		if (isMouseInside) spClick.Render(box.GetX(), box.GetY());
		else sp.Render(box.GetX(), box.GetY());
	}
}


bool ArrowButton::Is(std::string type)
{
	return type == "ArrowButton" ? true : false;
}

void ArrowButton::Activate()
{
	if (increase)
	{
		if (father->Is("LevelOption"))
		{
			if (father->GetValue() < 9)
			{
				father->SetValue(father->GetValue() + 1);
				clickSound.Play(0);
			}
		}
		else if (father->Is("SoundOption"))
		{
			if (father->GetValue() < 3)
			{
				father->SetValue(father->GetValue() + 1);
				clickSound.Play(0);
			}
		}
	}
	else if (!increase)
	{
		if (father->Is("LevelOption"))
		{
			if (father->GetValue() > 1)
			{
				father->SetValue(father->GetValue() - 1);
				clickSound.Play(0);
			}
		}
		else if (father->Is("SoundOption"))
		{
			if (father->GetValue() > 1)
			{
				father->SetValue(father->GetValue() - 1);
				clickSound.Play(0);
			}
		}
	}
}



