/*
 * Geyser.cpp
 *
 *  Created on: Jul 7, 2014
 *      Author: Gabriel Naves
 */

#include "../include/Geyser.h"

Geyser::Geyser(float x, float y) : inactive("img/objects/geyserInactive.png", 2, 0.2, true),
                                   active("img/objects/geyserActive.png", 2, 0.2, true),
                                   activating("img/objects/geyserActivating.png", 5, 0.1, false)
{
    box.Set(x, y, inactive.GetWidth(), inactive.GetHeight());
    renderingBox.Set(x, y, activating.GetWidth(), activating.GetHeight());
    state = GeyserNamespace::INACTIVE;
}

void Geyser::Update(float dt)
{
    if (state == GeyserNamespace::INACTIVE) UpdateInactive(dt);
    else if (state == GeyserNamespace::ACTIVATING) ActivateGeyser(dt);
    else if (state == GeyserNamespace::ACTIVE) UpdateActive(dt);
    else if (state == GeyserNamespace::DEACTIVATING) Deactivate(dt);
}

void Geyser::UpdateInactive(float dt)
{
    inactive.Update(dt);
    timer.Update(dt);
    if (timer.Get() >= 5)
    {
        inactive.SetFrame(1);
        activating.SetFrame(1);
        state = GeyserNamespace::ACTIVATING;
        timer.Restart();
    }
}

void Geyser::ActivateGeyser(float dt)
{
    activating.Update(dt);
    timer.Update(dt);
    if (timer.Get() >= 0.4)
    {
        state = GeyserNamespace::ACTIVE;
        timer.Restart();
    }
}

void Geyser::UpdateActive(float dt)
{
    active.Update(dt);
    timer.Update(dt);
    if (timer.Get() >= 5)
    {
        active.SetFrame(1);
        activating.SetFrame(5);
        state = GeyserNamespace::DEACTIVATING;
        timer.Restart();
    }
}

void Geyser::Deactivate(float dt)
{
    activating.Update(dt, false);
    timer.Update(dt);
    if (timer.Get() >= 0.4)
    {
        state = GeyserNamespace::INACTIVE;
        timer.Restart();
    }
}

void Geyser::Render()
{
    switch (state)
    {
        case GeyserNamespace::INACTIVE:
            inactive.Render(renderingBox.GetX()-Camera::pos.GetX(), renderingBox.GetY()-Camera::pos.GetY());
            break;
        case GeyserNamespace::ACTIVATING:
            activating.Render(renderingBox.GetX()-Camera::pos.GetX(), renderingBox.GetY()-Camera::pos.GetY());
            break;
        case GeyserNamespace::ACTIVE:
            active.Render(renderingBox.GetX()-Camera::pos.GetX(), renderingBox.GetY()-Camera::pos.GetY());
            break;
        case GeyserNamespace::DEACTIVATING:
            activating.Render(renderingBox.GetX()-Camera::pos.GetX(), renderingBox.GetY()-Camera::pos.GetY());
            break;
    }
}

void Geyser::NotifyCollision(GameObject& other)
{

}

bool Geyser::IsDead()
{
    return false;
}

bool Geyser::Is(std::string type)
{
    return type == "Geyser" ? true : false;
}
