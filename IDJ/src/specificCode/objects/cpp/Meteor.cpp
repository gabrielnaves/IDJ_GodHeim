/*
 * Meteor.cpp
 *
 *  Created on: Jul 7, 2014
 *      Author: icaro
 */

#include "../include/Meteor.h"

Meteor::Meteor(float x, float y, float X, float Y) : sp("img/level2/meteorFalling.png", 5,0.9,false)
{
	box.Set(x,y,sp.GetWidth(),sp.GetHeight());
	state = MeteorNamespace::FALLING;
	prevState = state;
	dead = false;
	rotation = atan((Y-y)/(X-x));
}

void Meteor::SetState(MeteorNamespace::State newState)
{
	prevState = state;
	state = newState;
}

void Meteor::Update(float dt)
{
	float FALLING_SPEED = MeteorNamespace::FALLING_SPEED;
	sp.Update(dt);
	if (state == MeteorNamespace::FALLING) box.MoveRect(FALLING_SPEED*cos(rotation),FALLING_SPEED*sin(rotation));
	if (state == MeteorNamespace::MELTING) explosion.Update(dt);
	if (explosion.Get()>0.6) box.MoveRect(0,1);
}
void Meteor::Render()
{
	sp.Render(box.GetX()-Camera::pos.GetX(), box.GetY()-Camera::pos.GetY());
}
void Meteor::NotifyCollision(GameObject& other)
{
	if (other.Is("Lava") and prevState == MeteorNamespace::FALLING)
	{
		SetState(MeteorNamespace::MELTING);
		sp.Open("img/level2/meteorMelting.png");
		box.MoveRect(0,20);
		sp.SetFrameCount(6);
		sp.SetFrameTime(0.4);
		sp.SetFrame(1);
	}
	if (other.Is("Loki"))
	{
		Loki::characterLoki->Kill();
	}
	if (other.Is("Thor"))
	{
		Thor::characterThor->Kill();
	}
}
bool Meteor::IsDead()
{
	return (explosion.Get() > 5 ? true:false);
}
bool Meteor::Is(std::string type)
{
	return type == "Meteor" ? true : false;
}
