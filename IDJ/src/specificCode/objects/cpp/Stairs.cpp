/*
 * Stairs.cpp
 *
 *  Created on: Jun 8, 2014
 *      Author: Gabriel Naves
 */

#include "../include/Stairs.h"

bool Stairs::IsStairsBelow(Rect character)
{
    return (character.GetY()+character.GetW()<box.GetY() ? true : false);
}

//------------------------------------------
Stairs::Stairs(std::string stairs, int x, int y) : stairsSp(stairs)
{
    box.Set(x,y,stairsSp.GetWidth(),stairsSp.GetHeight());
}

void Stairs::Render()
{
    stairsSp.Render(box.GetX()-Camera::pos.GetX(), box.GetY()-Camera::pos.GetY());
}

void Stairs::NotifyCollision(GameObject& other)
{
    if (other.Is("Loki") or other.Is("Thor"))
    {
        Character *character;
        if (other.Is("Loki"))
        {
            character = Loki::characterLoki;
            Loki::characterLoki->cannotTransform = true;
        }
        if (other.Is("Thor")) character = Thor::characterThor;
        if (CanClimb(character) and character->actionState != CLIMBING)
            if (character->vertical != 0)
            {
            	//centralizes on the stairs
                character->box.SetPoint(box.GetX()+box.GetW()/2-character->box.GetW()/2,character->box.GetY());
            	character->SetActionState(CLIMBING);
            }
        if ((character->horizontal == 1 or character->horizontal == -1) and character->actionState == CLIMBING)
        	character->SetActionState(NONE);
    }
}

/**
 * Determines if the character is close enough to the Stairs so he can climb on it
 */
bool Stairs::CanClimb(Character *character)
{
	if (character->box.GetX() > box.GetX()+box.GetW()-25 or character->box.GetX()+character->box.GetW() < box.GetX()+25)
		return false;
	if (character->box.GetY()+character->box.GetH() < box.GetY() or character->box.GetY() > box.GetY()+box.GetH())
		return false;
	return (true);
}

bool Stairs::Is(std::string type)
{
    return(type == "Stairs" ? true : false);
}

void Stairs::Update(float dt)
{
	if (Thor::characterThor == NULL or Loki::characterLoki == NULL) return;

	InteractsWith(Thor::characterThor);
	InteractsWith(Loki::characterLoki);

	prevThor = Thor::characterThor->box;
	prevLoki = Loki::characterLoki->box;
}

/**
 * Verifies necessary interactions with the characters
 */
void Stairs::InteractsWith(Character *character)
{
	if (!IsCloseTo(character)) return;
	if (ShouldDrop(character)) Drop(character);
	character->standingOnObject = false;
	if (ShouldStandOnStairs(character)) Stand(character);
	if (character->standingOnObject == true and character->vertical<0)
	{
		character->SetActionState(CLIMBING);
		character->standingOnObject = false;
		character->box.MoveRect(0,1);
	}
}

bool Stairs::IsCloseTo(Character *character)
{
	if (character->box.GetY() + character->box.GetH() < box.GetY() - 15) return (false);
	if (character->box.GetY() > box.GetY() + box.GetH() + 50) return (false);
	if (character->box.GetX() > box.GetX() + box.GetW() + 25) return (false);
	if (character->box.GetX() + character->box.GetW() < box.GetX() - 25) return (false);
	return(true);
}

/**
 * Drops the character from the Stairs when it is not colliding with it.
 */
bool Stairs::ShouldDrop(Character *character)
{
	if (character->actionState == CLIMBING) //as to not return true even though it is not climbing the Stairs
		return (!Collision::IsColliding(character->box,box,character->rotation,rotation));
	return(false);
}

void Stairs::Drop(Character *character)
{
	character->SetActionState(NONE);
}

bool Stairs::ShouldStandOnStairs(Character *character)
{
	Rect prevChar = character->Is("Thor") ? prevThor : prevLoki;
	if (!(character->box.GetY()+character->box.GetH() >= box.GetY() and prevChar.GetY()+prevChar.GetH() <= box.GetY()))
		return (false);
	if (character->box.GetX() > box.GetX()+box.GetW()-25 or character->box.GetX()+character->box.GetW() < box.GetX()+25)
		return(false);
	return(true);
}

void Stairs::Stand(Character *character)
{
	character->standingOnObject = true;
    character->box.MoveRect(0, box.GetY()-(character->box.GetY()+character->box.GetH()));
	character->SetActionState(NONE);
	character->SetVState(STANDING);
}
