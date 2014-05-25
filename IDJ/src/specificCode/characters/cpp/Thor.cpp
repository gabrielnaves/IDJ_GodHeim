/*
 * Thor.cpp
 *
 *  Created on: May 19, 2014
 *      Author: Gabriel Naves
 */

#include "../include/Thor.h"

Thor* Thor::characterThor;

Thor::Thor(float x, float y, MovementMap movMap) : Character(movMap)
{
    hp = 100;
    rotation = 0;
    tempCharacterSp.Open("img/tempThor.jpg");
    box.Set(x-tempCharacterSp.GetWidth()/2, y-tempCharacterSp.GetHeight()/2, tempCharacterSp.GetWidth(), tempCharacterSp.GetHeight());
    characterThor = this;
}

Thor::~Thor()
{
    characterThor = NULL;
}

void Thor::Input()
{
    int horizontal = 0;
    InputManager &input = InputManager::GetInstance();
    //sets the directions in which the camera must move
    if (input.KeyPress(SDLK_l) || input.IsKeyDown(SDLK_l))
        horizontal += 1;
    if (input.KeyPress(SDLK_j) || input.IsKeyDown(SDLK_j))
        horizontal -= 1;
    UpdateHorizontalState(horizontal);

    if (input.KeyPress(SDLK_i) and vState == STANDING)
        vState = JUMPING;
}


void Thor::Move(float dt)
{
    UpdateSpeed(dt);
    if (vState == JUMPING) vState = FALLING;
    box.MoveRect(speed.GetX()*dt,speed.GetY()*dt);
}

void Thor::Update(float dt)
{
    Input();
    Move(dt);
    CheckMovementLimits();
}

void Thor::Render()
{
    tempCharacterSp.Render(box.GetX()-Camera::pos.GetX(), box.GetY()-Camera::pos.GetY());
}

void Thor::NotifyCollision(GameObject& other)
{

}

bool Thor::Is(std::string type)
{
    return type == "Thor" ? true : false;
}
