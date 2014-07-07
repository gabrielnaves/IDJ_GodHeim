/*
 * ChainedDragon.cpp
 *
 *  Created on: Jul 7, 2014
 *      Author: Gabriel Naves
 */

#include "../include/ChainedDragon.h"

ChainedDragon::ChainedDragon(float x, float y) : sp("img/characters/dragon.png", 14, 0.1, true)
{
    box.Set(x, y, sp.GetWidth(), sp.GetHeight());
    facingRight = true;
}

void ChainedDragon::Update(float dt)
{

}

void ChainedDragon::Render()
{
    SDL_RendererFlip flip;
    flip = (facingRight ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
    sp.Render(box.GetX()-Camera::pos.GetX(), box.GetY()-Camera::pos.GetY(), rotation, flip);
}

void ChainedDragon::NotifyCollision(GameObject& other)
{

}

bool ChainedDragon::IsDead()
{
    return false;
}

bool ChainedDragon::Is(std::string type)
{
    return type == "ChainedDragon" ? true : false;
}
