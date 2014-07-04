/*
 * Rope.cpp
 *
 *  Created on: Jul 4, 2014
 *      Author: icaro
 */

#include "../include/Rope.h"

Rope::Rope(std::string rope, int x, int y) : ropeSp(rope)
{
    box.Set(x,y,ropeSp.GetWidth(),ropeSp.GetHeight());
    thorClimbing = lokiClimbing = false;
}

void Rope::Render()
{
    ropeSp.Render(box.GetX()-Camera::pos.GetX(), box.GetY()-Camera::pos.GetY());
}

void Rope::NotifyCollision(GameObject& other)
{
    if (other.Is("Loki") or other.Is("Thor"))
    {
        Character *character;
        if (other.Is("Loki"))
        {
            character = Loki::characterLoki;
            Loki::characterLoki->collidesWithRope = true;
        }
        if (other.Is("Thor")) character = Thor::characterThor;
        if (character->vertical > 0 and character->actionState != CLIMBING)
        {
            character->SetActionState(CLIMBING);
            character->box.SetPoint(box.GetX()+box.GetW()/2-character->box.GetW()/2,character->box.GetY());
            other.Is("Loki") ? lokiClimbing = true : thorClimbing = true;
        }
    }
}

bool Rope::Is(std::string type)
{
    return(type == "Rope" ? true : false);
}

void Rope::Update(float dt)
{
    if (thorClimbing)
    {
        if (Thor::characterThor->horizontal == 1 or Thor::characterThor->horizontal ==-1)
            Drop(Thor::characterThor);
        if (!Collision::IsColliding(box,Thor::characterThor->box,0,0))
            Drop(Thor::characterThor);
    }
    if (lokiClimbing)
    {
        if (Loki::characterLoki->horizontal == 1 or Loki::characterLoki->horizontal == -1)
            Drop(Loki::characterLoki);
        if (!Collision::IsColliding(box,Loki::characterLoki->box,0,0))
            Drop(Loki::characterLoki);
    }
}

void Rope::Drop(Character *character)
{
    character->Is("Thor") ? thorClimbing = false : lokiClimbing = false;
    character->SetActionState(NONE);
}
