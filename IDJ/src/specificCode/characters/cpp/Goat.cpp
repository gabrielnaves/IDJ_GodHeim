/*
 * Goat.cpp
 *
 *  Created on: Jun 12, 2014
 *      Author: arthur
 */

#include "../include/Goat.h"

Goat::Goat(float x, float y): sp("img/characters/goatWalk.png", 4, 0.1, true)
{
	box.Set(x-sp.GetWidth()/2, y-sp.GetHeight()/2, sp.GetWidth(), sp.GetHeight());
	rotation = 0;
	goatState = MOV_RIGHT;
	hp = 10;
}

void Goat::Update(float dt)
{
	timer.Update(dt);
	sp.Update(dt);
	UpdateState();
	Move(dt);
}

void Goat::UpdateState()
{
	if (timer.Get() > MAX_TIME)
	{
		if (goatState == MOV_RIGHT) goatState = STAND_RIGHT;
		else if (goatState == STAND_RIGHT) goatState = MOV_LEFT;
		else if (goatState == MOV_LEFT) goatState = STAND_LEFT;
		else goatState = MOV_RIGHT;
		timer.Restart();
	}
}

void Goat::Render()
{
	if ((goatState == MOV_RIGHT) || (goatState == STAND_RIGHT))
	{
		sp.Render(box.GetX()-Camera::pos.GetX(), box.GetY()-Camera::pos.GetY());
	}
	else
	{
		sp.Render(box.GetX()-Camera::pos.GetX(), box.GetY()-Camera::pos.GetY(), 0, SDL_FLIP_HORIZONTAL);
	}
}

void Goat::NotifyCollision(GameObject & other)
{
	if (other.Is("LokiBullet"))
	{
	    hp -= DAMAGE;
	    if (IsDead()) Die();
	}
}

void Goat::Die()
{
    Sprite goatDeath("img/characters/penguindeath.png", 5, 0.1);
    StillAnimation *sa = new StillAnimation(box.Center().GetX(),box.Center().GetY(),rotation,goatDeath,0.5,true);
    Game::GetInstance().GetCurrentState().AddObject(sa);

    Sound goatCry ("audio/SOUNDTRACK MODE/Bode.ogg");
    goatCry.Play(0);
}

bool Goat::IsDead()
{
	return (hp <= 0 ? true : false);
}

bool Goat::Is(std::string type)
{
	return type == "Goat" ? true : false;
}

void Goat::Move(float dt)
{
	if (goatState == MOV_RIGHT)	box.MoveRect(VEL*dt,0);
	else if (goatState == MOV_LEFT)	box.MoveRect(-VEL*dt,0);
	else {}
}
