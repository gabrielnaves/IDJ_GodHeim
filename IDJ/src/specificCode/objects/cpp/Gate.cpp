/*
 * Gate.cpp
 *
 *  Created on: Jul 6, 2014
 *      Author: icaro
 */

#include "../include/Gate.h"

Gate::Gate(std::string gateSp, int x, int y) : gateSp(gateSp, 6, 0.1, false)
{
    box.Set(x,y,this->gateSp.GetWidth(),this->gateSp.GetHeight());
    active = false;
    prevThor = prevLoki = Rect();
}

bool Gate::IsActive()
{
	return (IsCloseTo(Thor::characterThor) or IsCloseTo(Loki::characterLoki)) ? true : false;
}

/**
 * Determines if the character is close enough to the gate to drop it
 */
bool Gate::IsCloseTo(Character *character)
{
	if (character->box.GetY() + character->box.GetH() < box.GetY() - 15) return (false);
	if (character->box.GetY() > box.GetY() + box.GetH() + 50) return (false);
	if (character->box.GetX() > box.GetX() + box.GetW() + 25) return (false);
	if (character->box.GetX() + character->box.GetW() < box.GetX() - 25) return (false);
	return(true);
}

void Gate::Update(float dt)
{
	if (Thor::characterThor == NULL or Loki::characterLoki == NULL) return;
	active = IsActive();
	UpdateSprite(dt);

	InteractsWith(Thor::characterThor);
	InteractsWith(Loki::characterLoki);

	prevThor = Thor::characterThor->box;
	prevLoki = Loki::characterLoki->box;
}

void Gate::InteractsWith(Character *character)
{
	if (!IsCloseTo(character)) return;
	if (ShouldDrop(character)) Drop(character);
	character->standingOnObject = false;
	if (ShouldStandOnStairs(character)) Stand(character);
	if (character->standingOnObject == true and character->vertical<0)
	{
		character->SetActionState(CLIMBING_GATE);
		character->standingOnObject = false;
		character->box.MoveRect(0,1);
	}
}

bool Gate::ShouldStandOnStairs(Character *character)
{
	Rect prevChar = character->Is("Thor") ? prevThor : prevLoki;
	if (!(character->box.GetY()+character->box.GetH() >= box.GetY() and prevChar.GetY()+prevChar.GetH() <= box.GetY()))
		return (false);
	if (character->box.GetX() > box.GetX()+box.GetW()-25 or character->box.GetX()+character->box.GetW() < box.GetX()+25)
		return(false);
	return(true);
}
void Gate::Stand(Character *character)
{
	character->standingOnObject = true;
    character->box.MoveRect(0, box.GetY()-(character->box.GetY()+character->box.GetH()));
	character->SetActionState(NONE);
	character->SetVState(STANDING);
}

/**
 * Drops the character from the gate when it is not colliding with it.
 */
bool Gate::ShouldDrop(Character *character)
{
	if (character->actionState == CLIMBING_GATE) //as to not return true even though it is not climbing the gate
		return (!Collision::IsColliding(character->box,box,character->rotation,rotation));
	return(false);
}

void Gate::Drop(Character *character)
{
	character->SetActionState(NONE);
}

/**
 * Updates the animation of the gate if necessary
 */
void Gate::UpdateSprite(float dt)
{
	if (active)
	{
		if (gateSp.GetCurrentFrame() < gateSp.GetFrameCount())
			gateSp.Update(dt);
	}
	if (!active)
	{
		if (gateSp.GetCurrentFrame() > 1)
			gateSp.Update(dt,false);
	}
}

void Gate::Render()
{
    gateSp.Render(box.GetX()-Camera::pos.GetX(), box.GetY()-Camera::pos.GetY());
}

void Gate::NotifyCollision(GameObject& other)
{
    if (other.Is("Loki") or other.Is("Thor"))
    {
        Character *character;
        if (other.Is("Loki"))
        {
            character = Loki::characterLoki;
            Loki::characterLoki->cannotTransform = true;
        }
        if (other.Is("Thor")) character = Thor::characterThor;
        if (CanClimb(character) and character->actionState != CLIMBING_GATE)
            if (character->vertical != 0)
                character->SetActionState(CLIMBING_GATE);
    }

}

/**
 * Determines if the character is close enough to the gate so he can climb on it
 */
bool Gate::CanClimb(Character *character)
{
	if (character->box.GetX() > box.GetX()+box.GetW()-25 or character->box.GetX()+character->box.GetW() < box.GetX()+25)
		return false;
	if (character->box.GetY()+character->box.GetH() < box.GetY() or character->box.GetY() > box.GetY()+box.GetH())
		return false;
	return (true);
}
bool Gate::Is(std::string type)
{
	return(type == "Gate" ? true : false);
}
