/*
 * Thor.cpp
 *
 *  Created on: May 19, 2014
 *      Author: Gabriel Naves
 *              Icaro Mota
 */

#include "../include/Thor.h"

Thor* Thor::characterThor;

Thor::Thor(float x, float y, MovementMap movMap) : Character(movMap)
{
    hp = 100;
    rotation = 0;
    tempCharacterSp.Open("img/Characters/tempThor.png");
    box.Set(x-tempCharacterSp.GetWidth()/2, y-tempCharacterSp.GetHeight()/2, tempCharacterSp.GetWidth(), tempCharacterSp.GetHeight());
    characterThor = this;
    actionState = NONE;
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
    if (input.KeyPress(SDLK_k) or input.IsKeyDown(SDLK_k))
        vertical -= 1;
    if (input.KeyPress(SDLK_u))
        actionButton = true;
}

void Thor::DecideAction()
{
}

void Thor::UpdateVerticalState()
{
    if (vertical == 1 and vState == STANDING)
        vState = JUST_JUMPED;
}

void Thor::Move(float dt)
{
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
    UpdateState();
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
        vState = STANDING;
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
        tempCharacterSp.Open("img/Characters/tempThorInvertido.png");
    if (hState == STANDING_RIGHT)
        tempCharacterSp.Open("img/Characters/tempThorInvertido.png");
    if (hState == MOVING_LEFT)
        tempCharacterSp.Open("img/Characters/tempThor.png");
    if (hState == STANDING_LEFT)
        tempCharacterSp.Open("img/Characters/tempThor.png");
}
