/*
 * Meteor.cpp
 *
 *  Created on: Jul 7, 2014
 *      Author: icaro
 */

#include "../include/Meteor.h"

Meteor::Meteor(float x, float y) : sp("img/level2/meteorFalling.png", 5,0.9,false)
{
	box.Set(x,y,sp.GetWidth(),sp.GetHeight());
	state = MeteorNamespace::FALLING;
	prevState = state;
	dead = false;
}

void Meteor::SetState(MeteorNamespace::State newState)
{
	prevState = state;
	state = newState;
}

void Meteor::Update(float dt)
{
	sp.Update(dt);
	if (state == MeteorNamespace::FALLING) box.MoveRect(0,MeteorNamespace::FALLING_SPEED);
	if (state == MeteorNamespace::MELTING) explosion.Update(dt);
	if (explosion.Get()>0.2 and state == MeteorNamespace::MELTING)
	{
		SetState(MeteorNamespace::EXPLODING);
		sp.Open("img/level2/meteorExploding.png");
		sp.SetFrame(1);
		sp.SetFrameTime(0.15);
		box.MoveRect(0,-270);
	}
	if (state == MeteorNamespace::EXPLODING and sp.GetCurrentFrame() == sp.GetFrameCount()) dead = true;
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
		sp.SetFrameTime(0.2);
		sp.SetFrame(1);
	}
	if (other.Is("Loki"))
	{
		Loki::characterLoki->DealDamage();
	}
	if (other.Is("Thor"))
	{
		Thor::characterThor->DealDamage();
	}
}
bool Meteor::IsDead()
{
	return dead;
}
bool Meteor::Is(std::string type)
{
	return type == "Meteor" ? true : false;
}
