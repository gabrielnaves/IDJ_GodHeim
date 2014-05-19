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

/**
 * Adds an object to the object array.
 */
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

/**
 * Updates the object array.
 */
void State::UpdateArray(float dt)
{
    for (int i = 0; i < (int)objectArray.size(); i++)
        objectArray[i]->Update(dt);
}

/**
 * Renders the object array.
 */
void State::RenderArray()
{
    for (int i = 0; i < (int)objectArray.size(); i++)
        objectArray[i]->Render();
}
