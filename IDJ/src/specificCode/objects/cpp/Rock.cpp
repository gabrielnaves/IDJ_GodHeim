/*
 * Rock.cpp
 *
 *  Created on: Jul 5, 2014
 *      Author: icaro
 */

#include "../include/Rock.h"

Rock::Rock(std::string sprite,float x, float y)
{
	sp.Open(sprite);
	box.Set(x,y,sp.GetWidth(),sp.GetHeight());
	broke = false;
}

void Rock::Update(float dt) {}

void Rock::Render()
{
	sp.Render(box.GetX()-Camera::pos.GetX(), box.GetY()-Camera::pos.GetY());
}

void Rock::NotifyCollision(GameObject& other)
{
	if (other.Is("Thor"))
	    InteractsWith(Thor::characterThor);
	if (other.Is("Loki"))
		InteractsWith(Loki::characterLoki);
}

void Rock::InteractsWith(Character *character)
{
	if (character->box.GetX()+character->box.GetW() > box.GetX())
		character->box.SetPoint(box.GetX()-character->box.GetW(),character->box.GetY());
}

bool Rock::Is(std::string type)
{
	return (type == "Rock" ? true : false);
}

bool Rock::IsDead()
{
	return (broke);
}

void Rock::Die()
{
	broke = true;
    Sprite rockBreak("img/objects/pedracaindo.png", 9, 0.1);
    StillAnimation *sa = new StillAnimation(box.Center().GetX(),box.Center().GetY(),rotation,rockBreak,0.9,true);
    Game::GetInstance().GetCurrentState().AddObject(sa);
}
