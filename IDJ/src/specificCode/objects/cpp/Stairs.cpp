/*
 * Stairs.cpp
 *
 *  Created on: Jun 8, 2014
 *      Author: Gabriel Naves
 */

#include "../include/Stairs.h"

Stairs::Stairs(std::string stairs, int x, int y, int frameCount, float frameTime)
{
    stairsSp.Open(stairs);
    stairsSp.SetFrameCount(frameCount);
    stairsSp.SetFrameTime(frameTime);
    stairsSp.SetRepeat(false);
    box.Set(x,y,stairsSp.GetWidth(),stairsSp.GetHeight());
    showAnimation = false;
}

Stairs::~Stairs() {}

/**
 * Verifies necessary interactions with the characters
 */
void Stairs::Update(float dt)
{
    Rect loki = Loki::characterLoki->box;
    //if the character is close to the stairs
    if ((loki.GetX() >= box.GetX() and (loki.GetX() + loki.GetW()) <= (box.GetX() + box.GetH())))
    {
        LookForCharacterAbove(Loki::characterLoki);
        ReleasesStairs(Loki::characterLoki);
        showAnimation = true;
    }
    else showAnimation = false;

    Rect thor = Thor::characterThor->box;
    if ((thor.GetX() >= box.GetX() and (thor.GetX() + thor.GetW()) <= (box.GetX() + box.GetH())))
    {
        LookForCharacterAbove(Thor::characterThor);
        ReleasesStairs(Thor::characterThor);
        showAnimation = true;
    }
    else showAnimation = false;

    if (showAnimation) stairsSp.Update(dt);
    else stairsSp.Update(dt, false);
}

/**
 * Sets canHoldStairs to false when the character is not on a valid area anymore
 */
void Stairs::ReleasesStairs(Character *character)
{
    if (character->canHoldStairs == false) return;
    //if the character is above the stairs
    if (character->box.GetY() <= box.GetY() - character->box.GetH() and character->IsClimbing())
        character->canHoldStairs = false;
    //if the character hits the ground
    if (character->GetVState() == 0 and character->box.GetY()+5 > box.GetY())
        character->CancelAction();
}

/**
 * Sees if the character is inside an valid area above the stairs so he can use it
 */
void Stairs::LookForCharacterAbove(Character *character)
{
    //if the character is inside an rectangle limited by the sides of the stairs
    if ((character->box.GetX() >= box.GetX()) and ((character->box.GetX()+character->box.GetW()) <= (box.GetX()+box.GetW())))
        //if the character is close enough in the y axis to go down the stairs
            if (character->box.GetY()<=(box.GetY()-character->box.GetH()+5))
                character->box.GetY()>=(box.GetY()-character->box.GetH()-5) ?
                character->canHoldStairs = true : character->canHoldStairs = false;
}

void Stairs::Render()
{
    stairsSp.Render(box.GetX()-Camera::pos.GetX(), box.GetY()-Camera::pos.GetY());
}

void Stairs::NotifyCollision(GameObject& other)
{
    if (other.Is("Loki"))
        (abs(other.box.Center().GetX() - box.Center().GetX()) >= box.GetW()/6) ? //if it is far from the middle of the stairs
                Loki::characterLoki->canHoldStairs = false : Loki::characterLoki->canHoldStairs = true;
    if (other.Is("Thor"))
        (abs(other.box.Center().GetX() - box.Center().GetX()) >= box.GetW()/6) ?
                Thor::characterThor->canHoldStairs = false : Thor::characterThor->canHoldStairs = true;
}

bool Stairs::Is(std::string type)
{
    return(type == "Stairs" ? true : false);
}
