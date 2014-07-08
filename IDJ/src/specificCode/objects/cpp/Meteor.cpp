/*
 * Meteor.cpp
 *
 *  Created on: Jul 7, 2014
 *      Author: icaro
 */

#include "../include/Meteor.h"

Meteor::Meteor(float x, float y, float X, float Y) : sp("img/level2/meteorFalling.png", 5,0.7,false)
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
	if (state == MeteorNamespace::MELTING) meltTime.Update(dt);
	if (meltTime.Get()>0.6 and state == MeteorNamespace::MELTING) box.MoveRect(0,1);
	if (meltTime.Get()>15) Fall();
	prevState = state;
}

void Meteor::Fall()
{
	sp.Open("img/level2/meteorFalling.png");
	sp.SetFrameCount(5);
	sp.SetFrameTime(0.7);
	sp.SetFrame(1);
	box.SetPoint(rand() % 200 + 300,-400);

	rotation = 1.0 + (rand() % 10)/11.0;

	SetState(MeteorNamespace::FALLING);
	meltTime.Restart();
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
		sp.SetFrameCount(6);
		sp.SetFrameTime(0.4);
		sp.SetFrame(1);
		box.MoveRect(0,40);
	}
	if (other.Is("Loki") or other.Is("Thor"))
	{
		if (other.box.GetX() > box.GetX()+box.GetW()+5 or other.box.GetX()+other.box.GetW() < box.GetX()-5) return;
    	if (other.box.GetY()+other.box.GetH() < box.GetY()-10 or other.box.GetY() > box.GetY()+box.GetH()+10) return;
	}
	if (other.Is("Loki"))
	{
		if (box.Center().Distance(Loki::characterLoki->box.Center()) < 75)
			Loki::characterLoki->Kill();
	}
	if (other.Is("Thor"))
	{
		if (box.Center().Distance(Thor::characterThor->box.Center()) < 75)
			Thor::characterThor->Kill();
	}
}
bool Meteor::IsDead()
{
	return (false);
}
bool Meteor::Is(std::string type)
{
	return type == "Meteor" ? true : false;
}
