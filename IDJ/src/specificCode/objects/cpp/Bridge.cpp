/*
 * Bridge.cpp
 *
 *  Created on: Jun 9, 2014
 *      Author: Gabriel Naves
 */

#include "../include/Bridge.h"

Bridge::Bridge(float x, float y)
{
    bridgeSp.Open("img/level1/bridge.png");
    box.Set(x, y, bridgeSp.GetWidth(), bridgeSp.GetHeight());
    rotation = 0;

    bridgeSegment.emplace_back(x+14, y+110, x+65, y+70);
    bridgeSegment.emplace_back(x+65, y+70, x+210, y+70);
    bridgeSegment.emplace_back(x+205, y+70, x+260, y+110);
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
            lokiColliding = false, loki->insideBridge = false;
        if (!Collision::IsColliding(thor->box, box, thor->rotation*2*M_PI/360, rotation*2*M_PI/360))
            thorColliding = false, thor->insideBridge = false;
    }
    else lokiColliding = thorColliding = loki->insideBridge = thor->insideBridge = false;

    if (lokiColliding)
        loki->box.MoveRect(0, CheckPointPosition(loki, lokiAbove));
    if (thorColliding)
        thor->box.MoveRect(0, CheckPointPosition(thor, thorAbove));
}

float Bridge::CheckPointPosition(Character* character, bool charAbove)
{
    Point p(character->box.Center());
    float height = character->box.GetH()/2;
    for (int i = 0; i < 3; i++)
        if (p.GetX() > bridgeSegment[i].GetLowestX() && p.GetX() <= bridgeSegment[i].GetHighestX())
        {
            if (charAbove)
            {
                if (character->GetVState() == VerticalState::STANDING)
                    return bridgeSegment[i].GetVerticalDistance(p + Point(0, height));
                else if (bridgeSegment[i].IsBelow(p + Point(0, height)))
                {
                    character->SetVState(VerticalState::STANDING);
                    return bridgeSegment[i].GetVerticalDistance(p + Point(0, height));
                }
            }
            if (!charAbove && bridgeSegment[i].IsAbove(p + Point(0, -height)))
            {
                character->speed.Set(character->speed.GetX(), 0);
                return bridgeSegment[i].GetVerticalDistance(p + Point(0, -height));
            }
        }
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

    if (charAbove) character->insideBridge = true;
}
