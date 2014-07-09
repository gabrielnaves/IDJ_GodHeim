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
	hasFallen = false;
}

void StoneBlock::Update(float dt)
{
	if (CloseTo(Thor::characterThor->box)) CharactersStandOnBlock(Thor::characterThor);
	if (CloseTo(Loki::characterLoki->box)) CharactersStandOnBlock(Loki::characterLoki);

	if (ShouldFall()) Fall();

	if (ItemFlags::belt)
	{
		if (CloseTo(Thor::characterThor->box)) Push();
	}
	else if (CloseTo(Thor::characterThor->box)) Blocks(Thor::characterThor);
	if (CloseTo(Loki::characterLoki->box)) Blocks(Loki::characterLoki);

	prevLoki = Loki::characterLoki->box;
	prevThor = Thor::characterThor->box;
}

void StoneBlock::Fall()
{
	if (box.GetY() < 39*55)
		box.SetPoint(7*55,box.GetY()+10);
	else if (hasFallen == false)
	{
		hasFallen = true;
		box.SetPoint(7*55,39*55);
	    Sound goatCry ("audio/Pedra caindo game.ogg");
	    goatCry.Play(0);
	}
}

bool StoneBlock::ShouldFall()
{
	return (box.GetX() > 7*55-5 and box.GetX() < 7*55+5) ? true : false;
}

void StoneBlock::Push()
{
	Character *character = Thor::characterThor;
	if (character->box.GetY() < box.GetY()+box.GetH() and character->box.GetY() + character->box.GetH() > box.GetY())
	{
		//blocks from colliding on the left
		if (ShouldCollideLeftWall(character,prevThor))
			box.SetPoint(character->box.GetX()+character->box.GetW(),box.GetY());
		//blocks from colliding on the right
		if (ShouldCollideRightWall(character,prevThor))
			box.SetPoint(character->box.GetX()-box.GetW(),box.GetY());
	}
}

bool StoneBlock::CloseTo(Rect character)
{
	return (box.Center().Distance(character.GetPoint()) > sqrt(pow(box.GetW(),2)+pow(box.GetH(),2))) ? false : true;
}

void StoneBlock::Blocks(Character *character)
{
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
}

void StoneBlock::CharactersStandOnBlock(Character *character)
{
	character->standingOnObject = false;
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
