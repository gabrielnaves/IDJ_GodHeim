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
    Loki *loki = Loki::characterLoki;
    Thor *thor = Thor::characterThor;

    if ((loki->box.GetX() >= box.GetX()) and ((loki->box.GetX()+loki->box.GetW()) <= (box.GetX()+box.GetW())))
    {
        if ((loki->box.GetY()+loki->box.GetH() <= box.GetY()) and ((loki->box.GetY()+loki->box.GetH())>=(box.GetY()-10)))
            loki->canUseStairs = true;
        else loki->canUseStairs = false;
    }
}
void Stairs::Render()
{
    stairsSp.Render(box.GetX()-Camera::pos.GetX(), box.GetY()-Camera::pos.GetY());
}

void Stairs::NotifyCollision(GameObject& other)
{
}

bool Stairs::IsDead()
{
    return(false);
}

bool Stairs::Is(std::string type)
{
    return(type == "Stairs" ? true : false);
}
