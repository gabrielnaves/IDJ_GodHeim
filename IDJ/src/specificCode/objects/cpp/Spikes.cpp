/*
 * Spikes.cpp
 *
 *  Created on: Jun 10, 2014
 *      Author: icaro
 */

#include "../include/Spikes.h"

Spikes::Spikes(std::string spikes, int x, int y) {
    spikesSp.Open(spikes);
    box.Set(x,y,spikesSp.GetWidth(),spikesSp.GetHeight());
}

Spikes::~Spikes() {}

void Spikes::Update(float dt)
{

}

void Spikes::Render()
{
    spikesSp.Render(box.GetX()-Camera::pos.GetX(), box.GetY()-Camera::pos.GetY());
}

bool Spikes::Is(std::string type)
{
    return (type == "Spikes" ? true : false);
}

void Spikes::NotifyCollision(GameObject &other)
{
    if (other.Is("Loki") or other.Is("Thor"))
    {
    	if (other.box.GetX() > box.GetX()+box.GetW()+5 or other.box.GetX()+other.box.GetW() < box.GetX()-5) return;
    	if (other.box.GetY()+other.box.GetH() < box.GetY()-10 or other.box.GetY() > box.GetY()+box.GetH()+10) return;
        Character *character;
        if (other.Is("Loki")) character = Loki::characterLoki;
        else character = Thor::characterThor;
        character->DealDamage();
    }
}
