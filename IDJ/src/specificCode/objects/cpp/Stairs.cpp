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
    Rect loki = Loki::characterLoki->box;
    if ((loki.GetX() >= box.GetX()) and ((loki.GetX()+loki.GetW()) <= (box.GetX()+box.GetW())))
        Loki::characterLoki->canHoldStairs = true;
}

bool Stairs::IsDead()
{
    return(false);
}

bool Stairs::Is(std::string type)
{
    return(type == "Stairs" ? true : false);
}
