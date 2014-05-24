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
    horizontal = 0;
    vertical = 0;
}

Thor::~Thor()
{
    characterThor = NULL;
}

void Thor::Input()
{
    InputManager &input = InputManager::GetInstance();
    //sets the directions in which the camera must move
    if (input.KeyPress(SDLK_l) || input.IsKeyDown(SDLK_l))
        horizontal+=1;
    if (input.KeyPress(SDLK_j) || input.IsKeyDown(SDLK_j))
        horizontal-=1;
    if (input.KeyPress(SDLK_i) || input.IsKeyDown(SDLK_i))
        vertical-=1;
    if (input.KeyPress(SDLK_k) || input.IsKeyDown(SDLK_k))
        vertical+=1;
    if (input.KeyPress(SDLK_u)) return; //TODO: action button
}


void Thor::Move(float dt)
{
    if (vertical!=0) Jump(dt);
    if (horizontal!=0) Walk(dt);
    CheckMovementLimits();
}

void Thor::Update(float dt)
{
    Input();
    Move(dt);
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
