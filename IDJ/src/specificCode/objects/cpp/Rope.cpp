/*
 * Rope.cpp
 *
 *  Created on: Jul 4, 2014
 *      Author: icaro
 */

#include "../include/Rope.h"

Rope::Rope(std::string rope, int x, int y, bool active, int frameCount, float frameTime) : ropeSp(rope,frameCount,frameTime)
{
    box.Set(x,y,ropeSp.GetWidth(),ropeSp.GetHeight());
    thorClimbing = lokiClimbing = false;
    this->active = active;
}

void Rope::Render()
{
    ropeSp.Render(box.GetX()-Camera::pos.GetX(), box.GetY()-Camera::pos.GetY());
}

void Rope::NotifyCollision(GameObject& other)
{
    if (!active) return;
    if (other.Is("Loki") or other.Is("Thor"))
    {
    	if (other.box.GetX() > box.GetX()+box.GetW()+5 or other.box.GetX()+other.box.GetW() < box.GetX()-5) return;
    	if (other.box.GetY()+other.box.GetH() < box.GetY()-10 or other.box.GetY() > box.GetY()+box.GetH()+10) return;
        Character *character;
        if (other.Is("Loki"))
        {
            character = Loki::characterLoki;
            Loki::characterLoki->cannotTransform = true;
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
	if (active and ropeSp.GetCurrentFrame() != ropeSp.GetFrameCount())
		ropeSp.Update(dt);
	else if (active and ropeSp.GetCurrentFrame() == ropeSp.GetFrameCount() and ropeSp.GetFrameCount() > 1)
	{
		ropeSp.Open("img/objects/rope.png");
		ropeSp.SetFrameCount(1);
		ropeSp.SetFrame(1);
		box.MoveRect(47,0);
		box.Set(box.GetX(),box.GetY(),ropeSp.GetWidth(),ropeSp.GetHeight());
	}
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

void Rope::Activate()
{
    active = true;
}
