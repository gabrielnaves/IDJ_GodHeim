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
             restSp("img/characters/wolfwalk(1).png", 5, 0.1, true),
             runSp("img/characters/wolfwalk.png", 4, 0.1, true),
             attackSp("img/characters/wolfattack.png", 5, 0.1, true)
{
    box.Set(x-restSp.GetWidth()/2, y-restSp.GetHeight()/2, restSp.GetWidth(), restSp.GetHeight());
    rotation = 0;
    hp = 1;
    this->facingRight = facingRight;
    attacking = false;
    state = WolfNamespace::RESTING;
    visionField.Set(box.GetX(), (box.GetY()+box.GetH())-110, visionDistance, 110);
}

Wolf::~Wolf() {}

void Wolf::Update(float dt)
{
    if (state == WolfNamespace::RESTING) Rest(dt);
    else if (state == WolfNamespace::RUNNING) Run(dt);
    else if (state == WolfNamespace::ATTACKING) Attack(dt);
}

void Wolf::Rest(float dt)
{
    Rect target(FindClosestCharacter());
    restSp.Update(dt);
    // If the closest character is within the wolf's field of view, run towards it
    if (Collision::IsColliding(target, visionField, 0, 0))
        state = WolfNamespace::RUNNING;
}

void Wolf::Run(float dt)
{
    Rect target(FindClosestCharacter());
    runSp.Update(dt);
    float distance = target.Center().GetX() - box.Center().GetX();
    float signal = (distance >= 0 ? 1 : -1);
    facingRight = (signal == 1 ? true : false);
    if (abs(distance) >= 50)
        box.MoveRect(dt*WolfNamespace::RUN_SPEED*signal, 0);
    else state = WolfNamespace::ATTACKING;
}

void Wolf::Attack(float dt)
{
    Rect target(FindClosestCharacter());
    attackSp.Update(dt);
    attackTimer.Update(dt);
    if (attackTimer.Get() >= 0.2)
        box.MoveRect((facingRight ? 1 : -1)*dt*WolfNamespace::ATTACK_SPEED, 0);
    if (attackTimer.Get() >= 0.5)
    {
        state = WolfNamespace::RUNNING;
        attackSp.SetFrame(1);
        attackTimer.Restart();
    }
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
        case WolfNamespace::RESTING:
            restSp.Render(box.GetX()-Camera::pos.GetX(), box.GetY()-Camera::pos.GetY(), rotation*2*M_PI/360,
                            (facingRight ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL));
            break;
        case WolfNamespace::RUNNING:
            runSp.Render(box.GetX()-Camera::pos.GetX(), box.GetY()-Camera::pos.GetY(), rotation*2*M_PI/360,
                           (facingRight ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL));
            break;
        case WolfNamespace::ATTACKING:
            attackSp.Render(box.GetX()-Camera::pos.GetX(), box.GetY()-Camera::pos.GetY(), rotation*2*M_PI/360,
                             (facingRight ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL));
            break;
        case WolfNamespace::RETURNING:
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
