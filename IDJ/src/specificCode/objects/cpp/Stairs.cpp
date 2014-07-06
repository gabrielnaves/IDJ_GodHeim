/*
 * Stairs.cpp
 *
 *  Created on: Jun 8, 2014
 *      Author: Gabriel Naves
 */

#include "../include/Stairs.h"

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
        if (IsCloseToStairs(character))
        {
            if (character->vertical != 0)
                {
                    character->SetActionState(CLIMBING);
                    character->box.SetPoint(box.GetX()+box.GetW()/2-character->box.GetW()/2,character->box.GetY());
                }
        }
    }
}

bool Stairs::Is(std::string type)
{
    return(type == "Stairs" ? true : false);
}

bool Stairs::IsStairsBelow(Rect character)
{
    return (character.GetY()+character.GetW()<box.GetY() ? true : false);
}

bool Stairs::IsStairsAbove(Rect character)
{
    return (character.GetY()>box.GetY()+box.GetH() ? true : false);
}

bool Stairs::IsCloseToStairs(Character *character)
{
	if (character->box.GetX() > box.GetX()+box.GetW()-5 or character->box.GetX()+character->box.GetW() < box.GetX()+5)
		return false;
	if (character->box.GetY()+character->box.GetH() < box.GetY() or character->box.GetY() > box.GetY()+box.GetH())
		return false;
	return (true);
}

bool Stairs::IsAboveStairs(Character *character)
{
	if (character->box.GetY()+character->box.GetH()>box.GetY()+1) return(false);
	if (character->box.GetX()>box.GetX()+box.GetW()-1) return(false);
	if (character->box.GetX()+character->box.GetW() < box.GetX()+1) return(false);
	return(true);
}

void Stairs::Update(float dt)
{
    Character *loki = Loki::characterLoki;
    Character *thor = Thor::characterThor;

    if (IsCloseToStairs(thor))
    {
    	InteractsWith(thor);
        thor->aboveStairs = IsAboveStairs(thor);
    }
    if (IsCloseToStairs(loki))
    {
    	InteractsWith(loki);
        loki->aboveStairs = IsAboveStairs(loki);
    }
}

/**
 * Verifies necessary interactions with the characters
 */
void Stairs::InteractsWith(Character *character)
{
	character->aboveStairs = false;
    if (IsStairsBelow(character->box) and character->vertical<0 and character->actionState != CLIMBING) //if is above the stairs and wants to climb down
    {
    	character->aboveStairs = true;
        character->SetActionState(CLIMBING);
        character->box.SetPoint(box.GetX()+box.GetW()/2-character->box.GetW()/2,box.GetY()-box.GetW()+2); //goes down a pixel and centralizes on the stairs
    }
    else if (IsStairsBelow(Rect(character->box.GetX(),character->box.GetY(),character->box.GetW(),character->box.GetH()))
            and character->vertical>0 and character->actionState == CLIMBING)
    {
    	character->aboveStairs = true;
    	character->SetActionState(NONE);
    }
    else if (IsStairsBelow(character->box) and character->vertical >= 0 and character->actionState != CLIMBING)
    {
        character->aboveStairs = true;
        character->box.SetPoint(character->box.GetX(),box.GetPoint().GetY()-character->box.GetH()); //corrects bugs
    	character->SetActionState(NONE);
        character->SetVState(STANDING);
    }
    else if (IsStairsAbove(character->box) and character->vertical>0 and character->actionState != CLIMBING) //if is below the stairs and wants to climb up
    {
        character->SetActionState(CLIMBING);
        character->box.SetPoint(box.GetX()+box.GetW()/2-character->box.GetW()/2,box.GetY()+box.GetH()+2); //goes up a pixel and centralizes on the stairs
    }
    //drops the stairs when finishes climbing it up
    else if (IsStairsAbove(Rect(character->box.GetX(),character->box.GetY()+20,character->box.GetW(),character->box.GetH()))
            and character->vertical<0 and character->actionState == CLIMBING)
    {
        character->SetActionState(NONE);
    }
    else if (character->vState == STANDING and character->vertical<0 and !IsStairsBelow(character->box))
    {
        character->SetActionState(NONE);
    }
    else if ((character->horizontal == 1 or character->horizontal == -1) and character->actionState == CLIMBING)
        character->SetActionState(NONE);
}
