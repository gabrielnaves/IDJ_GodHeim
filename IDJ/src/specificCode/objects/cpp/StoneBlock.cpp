/*
 * StoneBlock.cpp
 *
 *  Created on: Jul 6, 2014
 *      Author: icaro
 */

#include "../include/StoneBlock.h"

StoneBlock::StoneBlock(std::string sprite,float x, float y)
{
	sp.Open(sprite);
	box.Set(x,y,sp.GetWidth(),sp.GetHeight());
	prevLoki = prevThor = Rect();
}

void StoneBlock::Update(float dt)
{
	if (!ItemFlags::belt)
	{
		if (CloseTo(Thor::characterThor->box)) Blocks(Thor::characterThor);
	}
	if (CloseTo(Loki::characterLoki->box)) Blocks(Loki::characterLoki);

	prevLoki = Loki::characterLoki->box;
	prevThor = Thor::characterThor->box;
}

bool StoneBlock::CloseTo(Rect character)
{
	return (box.Center().Distance(character.GetPoint()) > sqrt(pow(box.GetW(),2)+pow(box.GetH(),2))) ? false : true;
}

void StoneBlock::Blocks(Character *character)
{
	character->standingOnObject = false;
	Rect prevChar = character->Is("Thor") ? prevThor : prevLoki;
	if (character->box.GetY() < box.GetY()+box.GetH() and character->box.GetY() + character->box.GetH() > box.GetY())
	{
		//blocks from colliding on the left
		if (ShouldCollideLeftWall(character,prevChar))
			character->box.SetPoint(box.GetX()-character->box.GetW(),character->box.GetY());
		//blocks from colliding on the right
		if (ShouldCollideRightWall(character,prevChar))
			character->box.SetPoint(box.GetX()+box.GetW(),character->box.GetY());
	}
	if (character->box.GetX()+character->box.GetW()/2 > box.GetX() and character->box.GetX()+character->box.GetW()/2 < box.GetX()+box.GetW())
	{
		//blocks from colliding above
		if (ShouldStand(character))
			Stand(character);
	}
}

bool StoneBlock::ShouldCollideLeftWall(Character *character, Rect prevChar)
{
	return character->box.GetX()+character->box.GetW() >= box.GetX() and prevChar.GetX()+prevChar.GetW() <= box.GetX() ? true : false;
}

bool StoneBlock::ShouldCollideRightWall(Character *character, Rect prevChar)
{
	return character->box.GetX() <= box.GetX()+box.GetW() and prevChar.GetX() >= box.GetX()+box.GetW() ? true : false;
}

bool StoneBlock::ShouldStand(Character *character)
{
	Rect prevChar = character->Is("Thor") ? prevThor : prevLoki;
	if (!(character->box.GetY()+character->box.GetH() >= box.GetY() and prevChar.GetY()+prevChar.GetH() <= box.GetY()))
		return (false);
	if (character->box.GetX() > box.GetX()+box.GetW()-25 or character->box.GetX()+character->box.GetW() < box.GetX()+25)
		return(false);
	return(true);
}

void StoneBlock::Stand(Character *character)
{
	character->standingOnObject = true;
    character->box.MoveRect(0, box.GetY()-(character->box.GetY()+character->box.GetH()));
	character->SetVState(STANDING);
}

void StoneBlock::Render()
{
	sp.Render(box.GetX()-Camera::pos.GetX(), box.GetY()-Camera::pos.GetY());
}
void StoneBlock::NotifyCollision(GameObject& other)
{
}

bool StoneBlock::Is(std::string type)
{
	return(type == "Block" ? true : false);
}
