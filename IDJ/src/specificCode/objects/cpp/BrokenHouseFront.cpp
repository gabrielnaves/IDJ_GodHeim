/*
 * BrokenHouse.cpp
 *
 *  Created on: Jun 8, 2014
 *      Author: icaro
 */

#include "../include/BrokenHouseFront.h"

BrokenHouseFront::BrokenHouseFront(float x, float y) {
   sp.Open("img/objects/houseFront.png");
   box.Set(x, y, sp.GetWidth(), sp.GetHeight());
   roof.Set(x+50, y+10, 120, 40);
   thorColliding = lokiColliding = false;
}

BrokenHouseFront::~BrokenHouseFront() {}

void BrokenHouseFront::Render()
{
    sp.Render(box.GetX()-Camera::pos.GetX(), box.GetY()-Camera::pos.GetY());
}

void BrokenHouseFront::Update(float dt)
{
    Loki* loki = Loki::characterLoki;
    Thor* thor = Thor::characterThor;

    if (loki->box.Center().Distance(box.Center()) > 200 && thor->box.Center().Distance(box.Center()) > 200)
        thorColliding = lokiColliding = false;
    else
    {
        if (!Collision::IsColliding(loki->box, box, loki->rotation*2*M_PI/360, 0)) lokiColliding = false;
        if (!Collision::IsColliding(thor->box, box, thor->rotation*2*M_PI/360, 0)) thorColliding = false;
    }

    if (lokiColliding && Collision::IsColliding(loki->box, roof, loki->rotation*2*M_PI/360, 0))
        CorrectPosition(loki, lokiBox);
    if (thorColliding && Collision::IsColliding(thor->box, roof, thor->rotation*2*M_PI/360, 0))
        CorrectPosition(thor, thorBox);

    lokiBox.Set(loki->box);
    thorBox.Set(thor->box);
}

void BrokenHouseFront::CorrectPosition(Character* character, Rect previousBox)
{
    // If the character was previously to the left of the roof
    if (previousBox.GetX()+previousBox.GetW() <= roof.GetX())
    {
        character->box.MoveRect(roof.GetX() - (character->box.GetX()+character->box.GetW()), 0);
    }
    // If the character was previously to the right of the roof
    else if (previousBox.GetX() >= roof.GetX()+roof.GetW()) {}
    // If the character was previously below the roof
    else if (previousBox.GetY() > roof.GetY())
    {
        character->box.MoveRect(0, roof.GetY()+roof.GetH() - character->box.GetY());
        character->speed.Set(character->speed.GetX(), 0);
    }
    // If the character was previously above the roof
    else
    {
        character->box.MoveRect(0, roof.GetY()-(character->box.GetY()+character->box.GetH()));
        character->SetVState(VerticalState::STANDING);
    }
}

bool BrokenHouseFront::Is(std::string type)
{
    return(type == "BrokenHouse" ? true : false);
}

void BrokenHouseFront::NotifyCollision(GameObject& other)
{
    if (other.Is("Loki")) lokiColliding = true;
    if (other.Is("Thor")) thorColliding = true;
}
