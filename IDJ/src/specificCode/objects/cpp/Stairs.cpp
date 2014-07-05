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
        if (IsCloseToStairs(character->box))
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

bool Stairs::IsCloseToStairs(Rect character)
{
    if (character.Center().Distance(box.Center()) < 2*box.GetH()/3)
        if (character.GetX() < box.GetX()+box.GetW()/3 and character.GetPoint().GetX() > box.GetX()-box.GetW()/3)
            return(true);
    return(false);
}

void Stairs::Update(float dt)
{
    Character *loki = Loki::characterLoki;
    Character *thor = Thor::characterThor;

    thor->aboveStairs = false;
    loki->aboveStairs = false;
    if (IsCloseToStairs(thor->box)) InteractsWith(thor);
    if (IsCloseToStairs(loki->box)) InteractsWith(loki);
}

/**
 * Verifies necessary interactions with the characters
 */
void Stairs::InteractsWith(Character *character)
{
    if (IsStairsBelow(character->box) and character->vertical<0 and character->actionState != CLIMBING) //if loki is above the stairs and wants to climb down
    {
        character->SetActionState(CLIMBING);
        character->box.SetPoint(box.GetX()+box.GetW()/2-character->box.GetW()/2,box.GetY()-box.GetW()+2); //goes down a pixel and centralizes on the stairs
    }
    else if (IsStairsBelow(Rect(character->box.GetX(),character->box.GetY(),character->box.GetW(),character->box.GetH()))
            and character->vertical>0 and character->actionState == CLIMBING)
    {
        character->SetActionState(NONE);
    }
    else if (IsStairsBelow(character->box) and character->vertical >= 0 and character->actionState != CLIMBING)
    {
        character->aboveStairs = true;
        character->box.SetPoint(character->box.GetX(),box.GetPoint().GetY()-character->box.GetH()); //corrects bugs
        character->SetVState(STANDING);
    }
    else if (IsStairsAbove(character->box) and character->vertical>0 and character->actionState != CLIMBING) //if loki is below the stairs and wants to climb up
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
