/*
 * Goat.cpp
 *
 *  Created on: Jun 12, 2014
 *      Author: arthur
 */

#include "../include/Goat.h"

Goat::Goat(float x, float y): spWalk("img/characters/goatWalk.png", 4, 0.15, true),
                              spStand("img/characters/bode comendo.png", 10, 0.2, true)
{
	box.Set(x-spWalk.GetWidth()/2, y-spWalk.GetHeight()/2, spWalk.GetWidth(), spWalk.GetHeight());
	rotation = 0;
	goatState = MOV_RIGHT;
	hp = 10;
}

void Goat::Update(float dt)
{
	timer.Update(dt);
	spWalk.Update(dt);
	spStand.Update(dt);
	UpdateState();
	Move(dt);
}

void Goat::UpdateState()
{
	if (timer.Get() > MAX_TIME)
	{
		if (goatState == MOV_RIGHT)
		{
		    spStand.SetFrame(4);
		    goatState = STAND_RIGHT;
		}
		else if (goatState == STAND_RIGHT)
		{
		    spWalk.SetFrame(1);
		    goatState = MOV_LEFT;
		}
		else if (goatState == MOV_LEFT)
		{
		    spStand.SetFrame(4);
		    goatState = STAND_LEFT;
		}
		else
        {
		    spWalk.SetFrame(1);
		    goatState = MOV_RIGHT;
        }
		timer.Restart();
	}
}

void Goat::Render()
{
	if (goatState == MOV_RIGHT)
		spWalk.Render(box.GetX()-Camera::pos.GetX(), box.GetY()-Camera::pos.GetY());
	if (goatState == STAND_RIGHT)
	    spStand.Render(box.GetX()-Camera::pos.GetX(), box.GetY()-Camera::pos.GetY(), 0, SDL_FLIP_HORIZONTAL);
	if (goatState == MOV_LEFT)
		spWalk.Render(box.GetX()-Camera::pos.GetX(), box.GetY()-Camera::pos.GetY(), 0, SDL_FLIP_HORIZONTAL);
	if (goatState == STAND_LEFT)
	    spStand.Render(box.GetX()-Camera::pos.GetX(), box.GetY()-Camera::pos.GetY());
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
    Sprite goatDeath("img/characters/goatDeath.png", 33, 0.1);
    StillAnimation *sa = new StillAnimation(box.Center().GetX(),box.Center().GetY(),rotation,goatDeath,3.6,true);
    Game::GetInstance().GetCurrentState().AddObject(sa);

    Item *meat = new Item(box.Center().GetX(), box.Center().GetY(),"img/characters/pernil.png", "Meat", true, true, true, 3.6);
    Game::GetInstance().GetCurrentState().AddObject(meat);

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
