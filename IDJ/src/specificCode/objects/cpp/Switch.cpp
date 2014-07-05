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
    //find conditions on which the switch will NOT be pressed
    if (Thor::characterThor == NULL or Loki::characterLoki == NULL)
        return;
    if (activated) return;
    Thor *thor = Thor::characterThor;
    Loki *loki = Loki::characterLoki;
    if (thor->box.Center().Distance(box.Center()) >= 40 and
            loki->box.Center().Distance(box.Center()) >= 40)
    {
        SetColliding("Thor",false);
        SetColliding("Loki",false);
        return;
    }
    if (!Collision::IsColliding(thor->box, box, thor->rotation*2*M_PI/360, rotation*2*M_PI/360))
        SetColliding("Thor",false);
    if (!Collision::IsColliding(loki->box, box, loki->rotation*2*M_PI/360, rotation*2*M_PI/360))
        SetColliding("Loki",false);
    if (!thorColliding and !lokiColliding) return;

    if (thorColliding) Activate(Thor::characterThor);
    if (lokiColliding) Activate(Loki::characterLoki);

}

void Switch::Activate(Character *character)
{
    if (character->pressSwitch)
    {
        activated = true;
        connectedObject->Activate();
        character->pressSwitch = false;
    }
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
        SetColliding("Thor",true);
    if (other.Is("Loki"))
        SetColliding("Loki",true);
}

bool Switch::Is(std::string type)
{
    return type == "Switch" ? true : false;
}

void Switch::SetColliding(std::string character,bool state)
{
    if (character == "Thor")
    {
        thorColliding = state;
        Thor::characterThor->canPressSwitch = state;
    }
    if (character == "Loki")
    {
        lokiColliding = state;
        Loki::characterLoki->canPressSwitch = state;
    }
}
