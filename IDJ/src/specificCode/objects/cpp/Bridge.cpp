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
    segment1.Set(x+10, y+110, x+65, y+70);
    segment2.Set(x+65, y+70, x+210, y+70);
    segment3.Set(x+210, y+70, x+260, y+110);
    lokiColliding = thorColliding = false;
}

Bridge::~Bridge()
{
    // TODO Auto-generated destructor stub
}

void Bridge::Update(float dt)
{
    Loki* loki = Loki::characterLoki;
    Thor* thor = Thor::characterThor;
    if (!Collision::IsColliding(loki->box, box, loki->rotation*2*M_PI/360, rotation*2*M_PI/360))
        lokiColliding = false;
    if (!Collision::IsColliding(thor->box, box, thor->rotation*2*M_PI/360, rotation*2*M_PI/360))
        thorColliding = false;

    if (lokiColliding)
    {
        Point p(loki->box.GetPoint());
        p = p + Point(loki->box.GetW()/2, loki->box.GetH());
        CheckPointPosition(p);
    }
    if (thorColliding)
    {
        Point p(thor->box.GetPoint());
        p = p + Point(thor->box.GetW()/2, thor->box.GetH());
        CheckPointPosition(p);
    }
}

void Bridge::CheckPointPosition(Point& p)
{
    if (p.GetX() < segment1.GetHighestX())
    {
        if (segment1.IsAbove(p))
            std::cout << "Above segment" << std::endl;
        else std::cout << "Below segment" << std::endl;
    }
    else if (p.GetX() >= segment2.GetLowestX() && p.GetX() < segment2.GetHighestX())
    {
        if (segment2.IsAbove(p))
            std::cout << "Above segment" << std::endl;
        else std::cout << "Below segment" << std::endl;
    }
    else
    {
        if (segment3.IsAbove(p))
            std::cout << "Above segment" << std::endl;
        else std::cout << "Below segment" << std::endl;
    }
}

void Bridge::Render()
{
    bridgeSp.Render(box.GetX()-Camera::pos.GetX(), box.GetY()-Camera::pos.GetY());
}

void Bridge::NotifyCollision(GameObject& other)
{
    if (other.Is("Loki")) lokiColliding = true;
    else if (other.Is("Thor")) thorColliding = true;
}

bool Bridge::IsDead()
{
    return false;
}

bool Bridge::Is(std::string type)
{
    return type == "Bridge" ? true : false;
}
