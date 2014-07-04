/*
 * Switch.cpp
 *
 *  Created on: Jul 4, 2014
 *      Author: Gabriel Naves
 */

#include "../include/Switch.h"

Switch::Switch(float x, float y, std::string initial, std::string final, GameObject* connectedObject)
{
    this->initialSprite.Open(initial);
    this->finalSprite.Open(final);
    box.Set(x-initialSprite.GetWidth()/2, y-initialSprite.GetHeight()/2,
            initialSprite.GetWidth(), initialSprite.GetHeight());
    activated = false;
    rotation = 0;
    this->connectedObject = connectedObject;
    thorColliding = lokiColliding = false;
}

void Switch::Update(float dt)
{
//    if (Thor::characterThor == NULL or Loki::characterLoki == NULL)
//        return;
//    Thor *thor = Thor::characterThor;
//    Loki *loki = Loki::characterLoki;
//    if (thor->box.Center().Distance(box.Center()) >= 30 and
//            loki->box.Center().Distance(box.Center()) >= 30)
//    {
//        thorColliding = lokiColliding = false;
//        return;
//    }
//    if (!Collision::IsColliding(thor->box, box, thor->rotation*2*M_PI/360, rotation*2*M_PI/360))
//        thorColliding = false;
//    if (!Collision::IsColliding(loki->box, box, loki->rotation*2*M_PI/360, rotation*2*M_PI/360))
//        lokiColliding = false;
//    if (activated) return;
//    if (!thorColliding and !lokiColliding) return;
    // TODO: find out if loki or thor are pressing the button
}

void Switch::Render()
{
    if (!activated)
        initialSprite.Render(box.GetX()-Camera::pos.GetX(), box.GetY()-Camera::pos.GetY(), rotation);
    else
        finalSprite.Render(box.GetX()-Camera::pos.GetX(), box.GetY()-Camera::pos.GetY(), rotation);
}

void Switch::NotifyCollision(GameObject& other)
{
    if (other.Is("Thor"))
        thorColliding = true;
    if (other.Is("Loki"))
        lokiColliding = true;
}

bool Switch::Is(std::string type)
{
    return type == "Switch" ? true : false;
}
