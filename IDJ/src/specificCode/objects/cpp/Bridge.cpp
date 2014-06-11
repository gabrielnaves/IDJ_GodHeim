/*
 * Bridge.cpp
 *
 *  Created on: Jun 9, 2014
 *      Author: Gabriel Naves
 */

#include "../include/Bridge.h"

Bridge::Bridge(float x, float y)
{
    bridgeSp.Open("img/primeira fase/ponte.png");
    box.Set(x, y, bridgeSp.GetWidth(), bridgeSp.GetHeight());
    rotation = 0;

    bridgeSegment.emplace_back(x+10, y+110, x+65, y+70);
    bridgeSegment.emplace_back(x+65, y+70, x+210, y+70);
    bridgeSegment.emplace_back(x+210, y+70, x+260, y+110);
    lokiColliding = thorColliding = false;
    lokiAbove = thorAbove = true;
}

Bridge::~Bridge() {}

void Bridge::Update(float dt)
{
    Loki* loki = Loki::characterLoki;
    Thor* thor = Thor::characterThor;
    if (box.Center().Distance(loki->box.Center()) < 300 || box.Center().Distance(thor->box.Center()) < 300)
    {
        if (!Collision::IsColliding(loki->box, box, loki->rotation*2*M_PI/360, rotation*2*M_PI/360))
            lokiColliding = false;
        if (!Collision::IsColliding(thor->box, box, thor->rotation*2*M_PI/360, rotation*2*M_PI/360))
            thorColliding = false;
    }
    else lokiColliding = thorColliding = false;

    if (lokiColliding && lokiAbove)
    {
        loki->box.MoveRect(0, CheckPointPosition(loki->box.GetPoint()+
                                                 Point(loki->box.GetW()/2, loki->box.GetH())));
    }
    if (thorColliding && thorAbove)
    {
        thor->box.MoveRect(0, CheckPointPosition(thor->box.GetPoint()+
                                                 Point(thor->box.GetW()/2, thor->box.GetH())));
    }
}

float Bridge::CheckPointPosition(Point p)
{
    for (int i = 0; i < 3; i++)
        if (p.GetX() > bridgeSegment[i].GetLowestX() && p.GetX() <= bridgeSegment[i].GetHighestX())
            return bridgeSegment[i].GetVerticalDistance(p);
    return 0;
}

void Bridge::Render()
{
    bridgeSp.Render(box.GetX()-Camera::pos.GetX(), box.GetY()-Camera::pos.GetY());
}

void Bridge::NotifyCollision(GameObject& other)
{
    if (other.Is("Loki") && lokiColliding == false)
        CharacterInside(Loki::characterLoki);
    else if (other.Is("Thor") && thorColliding == false)
        CharacterInside(Thor::characterThor);
}

bool Bridge::IsDead()
{
    return false;
}

bool Bridge::Is(std::string type)
{
    return type == "Bridge" ? true : false;
}

/**
 * Determines whether the character that is colliding with
 * the bridge is coming from above or below the bridge.
 */
void Bridge::CharacterInside(Character* character)
{
    Point center(character->box.Center());
    bool charAbove = false;

    if (center.GetX() < bridgeSegment[0].GetHighestX())
        charAbove = (bridgeSegment[0].IsAbove(center) ? true : false);
    else if (center.GetX() < bridgeSegment[1].GetHighestX())
        charAbove = (bridgeSegment[1].IsAbove(center) ? true : false);
    else charAbove = (bridgeSegment[2].IsAbove(center) ? true : false);

    if (character->Is("Loki"))
        lokiColliding = true, lokiAbove = charAbove;
    if (character->Is("Thor"))
        thorColliding = true, thorAbove = charAbove;
}
