/*
 * Thor.cpp
 *
 *  Created on: May 19, 2014
 *      Author: Gabriel Naves
 *              Icaro Mota
 */

#include "../include/Thor.h"

Thor* Thor::characterThor;

Thor::Thor(float x, float y, MovementMap& movMap) : Character(movMap)
{
    tempCharacterSp.Open("img/characters/tempThor.png");
    box.Set(x-tempCharacterSp.GetWidth()/2, y-tempCharacterSp.GetHeight()/2, tempCharacterSp.GetWidth(), tempCharacterSp.GetHeight());
    characterThor = this;
}

Thor::~Thor()
{
    characterThor = NULL;
}

void Thor::Input()
{
    horizontal = vertical = 0;
    InputManager &input = InputManager::GetInstance();
    //sets the directions in which the camera must move

    if (input.KeyPress(SDLK_l) || input.IsKeyDown(SDLK_l))
        horizontal += 1;
    if (input.KeyPress(SDLK_j) || input.IsKeyDown(SDLK_j))
        horizontal -= 1;
    if (input.KeyPress(SDLK_i))
        vertical += 1;
    if (input.IsKeyDown(SDLK_i))
        vertical = 2;
    if (input.KeyPress(SDLK_k) or input.IsKeyDown(SDLK_k))
        vertical -= 1;
    if (input.KeyPress(SDLK_u))
        actionButton = true;
}

void Thor::ReleasesStairs()
{
    actionState = NONE;
    vState = FALLING;
}

void Thor::HoldStairs()
{
    actionState = CLIMBING;
    box.SetPoint(box.GetPoint().GetX(),box.GetPoint().GetY()+1);
}

/**
 * Calls the right action Thor must do, depending on the situation
 */
void Thor::Act()
{
    if (actionState == CLIMBING)
        ReleasesStairs();
    else if (canHoldStairs)
        HoldStairs();
    actionButton = false;
}

void Thor::UpdateVerticalState()
{
    if (vertical == 1 and vState == STANDING)
        vState = JUST_JUMPED;
}

void Thor::Move(float dt)
{
    if (actionState == CLIMBING)
        Climb(dt);
    else
        UpdateSpeed(dt);
    box.MoveRect(speed.GetX()*dt,speed.GetY()*dt);
    Barrier::barrier->CheckCollision(this);
}

void Thor::UpdatesStateOnTheFall()
{
    if (vState == JUST_JUMPED) vState = JUMPING;
    if (speed.GetY() > 0) vState = FALLING;
}

void Thor::Update(float dt)
{
    Input();
    if (actionButton) Act();
    UpdateState();
    if (actionState == CLIMBING and !canHoldStairs) actionState = NONE;
    UpdateSprite();
    Move(dt);
    UpdatesStateOnTheFall();
    CheckMovementLimits();
}

void Thor::Render()
{
    tempCharacterSp.Render(box.GetX()-Camera::pos.GetX(), box.GetY()-Camera::pos.GetY());
}

void Thor::NotifyCollision(GameObject& other)
{
    if (other.Is("Stairs"))
    {
        if ((box.GetX() >= box.GetX()) and ((box.GetX()+box.GetW()) <= (other.box.GetX()+other.box.GetW())))
        {
                //if the character is close enough in the y axis to go down the stairs
                if (box.GetY()<=(other.box.GetY()-box.GetH()+50) and box.GetY()>=(other.box.GetY()-box.GetH()-2) and actionState != CLIMBING)
                {
                    box.SetPoint(box.GetX(),other.box.GetPoint().GetY()-box.GetH()); //corrects bugs
                    vState = STANDING;
                }
        }
    }
    if (other.Is("Spikes"))
        hp -= HP/20;
}

bool Thor::Is(std::string type)
{
    return type == "Thor" ? true : false;
}

/**
 * Updates the sprite based on the state of the character
 */
void Thor::UpdateSprite()
{
    if (hState == MOVING_RIGHT)
        tempCharacterSp.Open("img/characters/tempThorInvertido.png");
    if (hState == STANDING_RIGHT)
        tempCharacterSp.Open("img/characters/tempThorInvertido.png");
    if (hState == MOVING_LEFT)
        tempCharacterSp.Open("img/characters/tempThor.png");
    if (hState == STANDING_LEFT)
        tempCharacterSp.Open("img/characters/tempThor.png");
}
