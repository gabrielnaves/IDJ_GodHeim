/*
 * PlantBarrier.cpp
 *
 *  Created on: Jul 5, 2014
 *      Author: icaro
 */

#include "../include/PlantBarrier.h"

PlantBarrier::PlantBarrier(std::string sprite,float x, float y)
{
	sp.Open(sprite);
	box.Set(x,y,sp.GetWidth(),sp.GetHeight());
	dead = false;
}

void PlantBarrier::Update(float dt)
{

}

void PlantBarrier::Render()
{
	sp.Render(box.GetX()-Camera::pos.GetX(), box.GetY()-Camera::pos.GetY());
}

void PlantBarrier::NotifyCollision(GameObject& other)
{
	if (other.Is("Thor"))
		CollidesWith(Thor::characterThor);
	if (other.Is("Loki"))
		CollidesWith(Loki::characterLoki);
	if (other.Is("LokiBullet"))
		Die();
}

void PlantBarrier::CollidesWith(Character *character)
{
	if (character->box.GetX() < box.GetX()+box.GetW()) character->box.SetPoint(box.GetX()+box.GetW(),character->box.GetY());
}

void PlantBarrier::Die()
{
	dead = true;
    Sprite plantBurn("img/objects/plantBurn.png", 10, 0.1);
    StillAnimation *sa = new StillAnimation(box.Center().GetX(),box.Center().GetY(),rotation,plantBurn,1,true);
    Game::GetInstance().GetCurrentState().AddObject(sa);
}

bool PlantBarrier::Is(std::string type)
{
	return(type == "PlantBarrier" ? true:false);
}

bool PlantBarrier::IsDead()
{
	return(dead);
}
