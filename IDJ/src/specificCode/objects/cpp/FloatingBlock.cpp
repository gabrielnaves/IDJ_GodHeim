/*
 * FloatingBlock.cpp
 *
 *  Created on: Jul 7, 2014
 *      Author: arthur
 */

#include "../include/FloatingBlock.h"

FloatingBlock::FloatingBlock(std::string sprite, int x, int y, FloatingBlockState state,
                             float angle, float vel, float distance, float wait)
{
	this->state = state;
	block.Open(sprite);
	box.Set(x,y,block.GetWidth(),block.GetHeight()-20);
	prevBlockPos = box;
	prevLokiPos = prevThorPos = Rect();
	VEL = vel;
	DISTANCE = distance;
	alreadyMoved = 0;
	WAITTIME = wait;
	thorStanding = lokiStanding = false;
	movAngle = angle;
}

void FloatingBlock::Update(float dt)
{
	timer.Update(dt);
	UpdateState();
	Move(dt);

	if(Thor::characterThor && !(IsOnTop(Thor::characterThor)))
	{
		Thor::characterThor->standingOnObject = false;
		thorStanding = false;
	}
	if(Loki::characterLoki && !(IsOnTop(Loki::characterLoki)))
	{
		Loki::characterLoki->standingOnObject = false;
		lokiStanding = false;
	}
}

void FloatingBlock::Render()
{
	if (Thor::characterThor != NULL)
		prevThorPos = Thor::characterThor->box;
	if (Loki::characterLoki != NULL)
		prevLokiPos = Loki::characterLoki->box;
	prevBlockPos = box;

	block.Render(box.GetX()-Camera::pos.GetX(), box.GetY()-Camera::pos.GetY());
}

void FloatingBlock::NotifyCollision(GameObject& other)
{
	if (other.Is("Loki"))
	{
	    if (!ConfirmCharacterCollision(other)) return;
		if (prevLokiPos.GetY() + prevLokiPos.GetH() <= prevBlockPos.GetY())																//Loki coming from above;
		{
			if (prevLokiPos.GetX() + prevLokiPos.GetW() > prevBlockPos.GetX()
					|| prevLokiPos.GetX() < prevBlockPos.GetX() + prevBlockPos.GetW())													//Loki already on top position;
			{
				Loki::characterLoki->box.SetPoint(Loki::characterLoki->box.GetX(), box.GetY() - Loki::characterLoki->box.GetH());		//Moves Loki to standing position on top;
				Loki::characterLoki->SetVState(STANDING);
				Loki::characterLoki->standingOnObject = true;
				lokiStanding = true;
			}
		}
		else if (prevLokiPos.GetY() >= prevBlockPos.GetY() + prevBlockPos.GetH())														//Loki coming from below;
		{
			if (prevLokiPos.GetX() + prevLokiPos.GetW() > prevBlockPos.GetX()
					|| prevLokiPos.GetX() < prevBlockPos.GetX() + prevBlockPos.GetW())													//Loki already on below position;
			{
				Loki::characterLoki->box.SetPoint(Loki::characterLoki->box.GetX(), box.GetY() + box.GetH());							//Moves Loki to falling position on below;
				Loki::characterLoki->DealDamage();																						//Deal spike damage;
			}
		}
		else if (prevLokiPos.GetX() + prevLokiPos.GetW() < prevBlockPos.GetX() + prevBlockPos.GetW())														//Loki coming from left;
			Loki::characterLoki->box.SetPoint(box.GetX() - Loki::characterLoki->box.GetW(), Loki::characterLoki->box.GetY());			//Moves Loki to falling position on left side;

		else																															//Loki coming from right;
			Loki::characterLoki->box.SetPoint(box.GetX() + box.GetW(), Loki::characterLoki->box.GetY());								//Moves Loki to falling position on right side;

	}
	else if(other.Is("Thor"))
	{
	    if (!ConfirmCharacterCollision(other)) return;
		if (prevThorPos.GetY() + prevThorPos.GetH() <= prevBlockPos.GetY())																//Thor coming from above;
		{
			if (prevThorPos.GetX() + prevThorPos.GetW() > prevBlockPos.GetX()
					|| prevThorPos.GetX() < prevBlockPos.GetX() + prevBlockPos.GetW())													//Thor already on top position;
			{
				Thor::characterThor->box.SetPoint(Thor::characterThor->box.GetX(), box.GetY() - Thor::characterThor->box.GetH());		//Moves Thor to standing position on top;
				Thor::characterThor->SetVState(STANDING);
				Thor::characterThor->standingOnObject = true;
				thorStanding = true;
			}
		}
		else if (prevThorPos.GetY() >= prevBlockPos.GetY() + prevBlockPos.GetH())														//Thor coming from below;
		{
			if (prevThorPos.GetX() + prevThorPos.GetW() > prevBlockPos.GetX()
					|| prevThorPos.GetX() < prevBlockPos.GetX() + prevBlockPos.GetW())													//Thor already on below position;
			{
				Thor::characterThor->box.SetPoint(Thor::characterThor->box.GetX(), box.GetY() + box.GetH());							//Moves Thor to falling position on below;
				Thor::characterThor->DealDamage();																						//Deal spike damage;
			}
		}
		else if (prevThorPos.GetX() + prevThorPos.GetW() < prevBlockPos.GetX() + prevBlockPos.GetW())									//Thor coming from left;
			Thor::characterThor->box.SetPoint(box.GetX() - Thor::characterThor->box.GetW(), Thor::characterThor->box.GetY());			//Moves Thor to falling position on left side;

		else																															//Thor coming from right;
			Thor::characterThor->box.SetPoint(box.GetX() + box.GetW(), Thor::characterThor->box.GetY());								//Moves Thor to falling position on right side;

	}
}

bool FloatingBlock::ConfirmCharacterCollision(GameObject& character)
{
    if (character.box.GetX() > box.GetX()+box.GetW()) return false;
    if (character.box.GetX() + character.box.GetW() < box.GetX()) return false;
    if (character.box.GetY() > box.GetY()+box.GetH()) return false;
    if (character.box.GetY() + character.box.GetH() < box.GetY()) return false;
    return true;
}

void FloatingBlock::UpdateState()
{
	if (state == FORWARD)
	{
		if (alreadyMoved >= DISTANCE)
		{
			state = FWDSTOP;
			alreadyMoved = 0;
			timer.Restart();
		}
	}
	else if (state == FWDSTOP)
	{
		if (timer.Get() >= WAITTIME)
			state = BACKWARD;
	}
	else if (state == BACKWARD)
	{
		if (alreadyMoved >= DISTANCE)
		{
			state = BACKSTOP;
			alreadyMoved = 0;
			timer.Restart();
		}
	}
	else
	{
		if (timer.Get() >= WAITTIME)
			state = FORWARD;
	}
}

void FloatingBlock::Move(float dt)
{
    Point speed(VEL*cos(movAngle)*dt, VEL*sin(movAngle)*dt);
	if (state == FORWARD)
	{
		alreadyMoved += speed.Distance(Point());
		if (alreadyMoved > DISTANCE)
			box.MoveRect(speed.GetX(), speed.GetY() + (alreadyMoved - DISTANCE));
		else
			box.MoveRect(speed.GetX(), speed.GetY());
	}
	else if (state == BACKWARD)
	{
		alreadyMoved += speed.Distance(Point());
		if (alreadyMoved > DISTANCE)
			box.MoveRect(-speed.GetX(), -speed.GetY() - (alreadyMoved - DISTANCE));
		else
			box.MoveRect(-speed.GetX(), -speed.GetY());
	}
	if (Thor::characterThor && thorStanding && Thor::characterThor->GetVState() == STANDING)
	{
	    if (state == FORWARD)
	        Thor::characterThor->box.SetPoint(Thor::characterThor->box.GetX()+speed.GetX(), box.GetY() - Thor::characterThor->box.GetH());
	    else if (state == BACKWARD)
	        Thor::characterThor->box.SetPoint(Thor::characterThor->box.GetX()-speed.GetX(), box.GetY() - Thor::characterThor->box.GetH());
	}
	if (Loki::characterLoki && lokiStanding && Loki::characterLoki->GetVState() == STANDING)
	{
	    if (state == FORWARD)
	        Loki::characterLoki->box.SetPoint(Loki::characterLoki->box.GetX()+speed.GetX(), box.GetY() - Loki::characterLoki->box.GetH());
	    if (state == BACKWARD)
            Loki::characterLoki->box.SetPoint(Loki::characterLoki->box.GetX()-speed.GetX(), box.GetY() - Loki::characterLoki->box.GetH());
	}
}

bool FloatingBlock::IsOnTop(GameObject* character)
{
	if (character->Is("Thor"))
		return ( (Thor::characterThor->standingOnObject) && (character->box.GetY() + character->box.GetH() >= box.GetY()) && (character->box.GetX() + character->box.GetW() > box.GetX())
				&& (character->box.GetX() < box.GetX() + box.GetW()) ? true : false);
	else
		return ( (Loki::characterLoki->standingOnObject) && (character->box.GetY() + character->box.GetH() >= box.GetY()) && (character->box.GetX() + character->box.GetW() > box.GetX())
					&& (character->box.GetX() < box.GetX() + box.GetW()) ? true : false);
}

bool FloatingBlock::Is(std::string type)
{
	return (type == "FloatingBlock" ? true : false);
}

bool FloatingBlock::IsDead()
{
	return false;
}
