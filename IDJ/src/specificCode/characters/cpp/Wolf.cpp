/*
 * Wolf.cpp
 *
 *  Created on: Jun 29, 2014
 *      Author: Gabriel Naves
 */

#include "../include/Wolf.h"

/**
 * Constructor for the wolf. The wolf npc will
 * rest indefinitely. If a character comes within
 * its field of view, it gets up and attacks him.
 */
Wolf::Wolf(float x, float y, float visionDistance, bool facingRight) :
             restSp("img/characters/wolfwalk.png", 5, 0.1, true),
             runSp("img/characters/wolfwalk.png", 5, 0.1, true),
             attackSp("img/characters/wolfrun.png", 11, 0.1, true)
{
    box.Set(x-restSp.GetWidth()/2, y-restSp.GetHeight()/2, restSp.GetWidth(), restSp.GetHeight());
    rotation = 0;
    hp = 1;
    this->facingRight = facingRight;
    attacking = false;
    state = WolfState::RESTING;
    this->distance = visionDistance;
}

Wolf::~Wolf() {}

void Wolf::Update(float dt)
{
    if (state == WolfState::RESTING) Rest(dt);
    if (state == WolfState::RUNNING) Run(dt);
    else if (state == WolfState::ATTACKING) Attack(dt);
}

void Wolf::Rest(float dt)
{
    Rect target(FindClosestCharacter());
    restSp.Update(dt);
    // If the closest character is within the wolf's field of view, run towards it
    if (abs(target.GetY()-box.GetY()) <= 100 && box.GetY()+box.GetH() > target.GetY())
        if (facingRight && (target.Center().GetX()-box.Center().GetX() <= distance))
            state = WolfState::RUNNING;
}

void Wolf::Run(float dt)
{
}

void Wolf::Attack(float dt)
{
}

Rect Wolf::FindClosestCharacter()
{
    if (Loki::characterLoki->box.Center().Distance(box.Center()) <
            Thor::characterThor->box.Center().Distance(box.Center()))
        return Loki::characterLoki->box;
    else return Thor::characterThor->box;
}

void Wolf::Render()
{
    switch (state)
    {
        case WolfState::RESTING:
            restSp.Render(box.GetX()-Camera::pos.GetX(), box.GetY()-Camera::pos.GetY(), rotation*2*M_PI/360,
                            (facingRight ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL));
            break;
        case WolfState::RUNNING:
            runSp.Render(box.GetX()-Camera::pos.GetX(), box.GetY()-Camera::pos.GetY(), rotation*2*M_PI/360,
                           (facingRight ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL));
            break;
        case WolfState::ATTACKING:
            attackSp.Render(box.GetX()-Camera::pos.GetX(), box.GetY()-Camera::pos.GetY(), rotation*2*M_PI/360,
                             (facingRight ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL));
            break;
        case WolfState::RETURNING:
            walkSp.Render(box.GetX()-Camera::pos.GetX(), box.GetY()-Camera::pos.GetY(), rotation*2*M_PI/360,
                    (facingRight ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL));
            break;
    }
}

void Wolf::NotifyCollision(GameObject& other)
{
    if (other.Is("LokiBullet")) hp -= 1;
}

bool Wolf::IsDead()
{
    return hp <= 0 ? true : false;
}

bool Wolf::Is(std::string type)
{
    return type == "Wolf" ? true : false;
}
