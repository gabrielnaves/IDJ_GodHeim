/*
 * HpBar.cpp
 *
 *  Created on: Jul 5, 2014
 *      Author: icaro
 */

#include "../include/HpBar.h"

HpBar::HpBar(std::string sprite, std::string character, int x, int y) : sp(sprite,10,0.08)
{
	box.Set(x,y,sp.GetWidth(),sp.GetHeight());
	full = true;
	fill = empty = false;
	this->sprite = sprite;
	this->character = character;
}

HpBar::~HpBar() {}

void HpBar::Update(float dt)
{
	if (fill == true)
	{
		if (sp.GetCurrentFrame() == 1)
		{
			fill = false;
			full = true;
		}
		else sp.Update(dt,false);
	}
	if (empty == true)
	{
		if (sp.GetCurrentFrame() == 10)
		{
			empty = false;
			full = false;
		}
		else sp.Update(dt,true);
	}
}

void HpBar::Render()
{
	sp.Render(box.GetX(),box.GetY());
}

bool HpBar::IsDead() {return(!full);}

bool HpBar::Is(std::string type)
{
	return (type == character+"Hp" ? true : false);
}

void HpBar::Empty()
{
	empty = true;
}
void HpBar::Fill()
{
	fill = true;
}

std::string HpBar::GetSp()
{
	return(sprite);
}
std::string HpBar::GetCharacter()
{
	return(character);
}
