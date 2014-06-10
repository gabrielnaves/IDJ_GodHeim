/*
 * Stairs.cpp
 *
 *  Created on: Jun 8, 2014
 *      Author: Gabriel Naves
 */

#include "../include/Stairs.h"

Stairs::Stairs()
{
    stairsSp.Open("img/Objects/stairs.png");
    box.Set(605,440,stairsSp.GetWidth(),stairsSp.GetHeight());
}

Stairs::~Stairs()
{
    // TODO Auto-generated destructor stub
}

void Stairs::Update(float dt)
{
    LookForCharacterAbove(Loki::characterLoki);
    LookForCharacterAbove(Thor::characterThor);
    ReleasesStairs(Loki::characterLoki);
    ReleasesStairs(Thor::characterThor);
}

/**
 * Sets canHoldStairs to false when the character is not on a valid area anymore
 */
void Stairs::ReleasesStairs(Character *character)
{
    if (character->canHoldStairs == false) return;
    //if the character is above the stairs
    if (character->box.GetY() <= box.GetY() - character->box.GetH())
        character->canHoldStairs = false;
    //if the character hits the ground
    if (character->vState == 0)
        character->canHoldStairs = false;
}

/**
 * Sees if the character is inside an valid area above the stairs so he can use it
 */
void Stairs::LookForCharacterAbove(Character *character)
{
    //if the character is inside an rectangle limited by the sides of the stairs
    if ((character->box.GetX() >= box.GetX()) and ((character->box.GetX()+character->box.GetW()) <= (box.GetX()+box.GetW())))
        //if the character is close enough in the y axis to go down the stairs
        if (character->box.GetY()<=(box.GetY()-character->box.GetH()+10) and
            character->box.GetY()>=(box.GetY()-character->box.GetH()-10))
            character->canHoldStairs = true;
}

void Stairs::Render()
{
    stairsSp.Render(box.GetX()-Camera::pos.GetX(), box.GetY()-Camera::pos.GetY());
}

void Stairs::NotifyCollision(GameObject& other)
{

    if (other.Is("Loki"))
        (abs(other.box.Center().GetX() - box.Center().GetX()) >= box.GetW()/4) ? //if it is far from the middle of the stairs
                Loki::characterLoki->canHoldStairs = false : Loki::characterLoki->canHoldStairs = true;
    if (other.Is("Thor"))
        (abs(other.box.Center().GetX() - box.Center().GetX()) >= box.GetW()/4) ?
                Thor::characterThor->canHoldStairs = false : Thor::characterThor->canHoldStairs = true;
}

bool Stairs::IsDead()
{
    return(false);
}

bool Stairs::Is(std::string type)
{
    return(type == "Stairs" ? true : false);
}
