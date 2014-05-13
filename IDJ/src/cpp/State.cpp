/*
 * State.cpp
 *
 *  Created on: May 3, 2014
 *      Author: Gabriel Naves
 */

#include "../include/State.h"

State::State()
{
    requestDelete = false;
    requestQuit = false;
}

State::~State() {}

void State::AddObject(GameObject* ptr)
{
    objectArray.emplace_back(ptr);
}

bool State::RequestedDelete()
{
    return requestDelete;
}

bool State::RequestedQuit()
{
    return requestQuit;
}

void State::UpdateArray(float dt)
{
    for (int i = 0; i < (int)objectArray.size(); i++)
        objectArray[i]->Update(dt);
}

void State::RenderArray()
{
    for (int i = 0; i < (int)objectArray.size(); i++)
        objectArray[i]->Render();
}
