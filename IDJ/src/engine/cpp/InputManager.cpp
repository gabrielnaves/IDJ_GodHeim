/*
 * InputManager.cpp
 *
 *  Created on: Apr 11, 2014
 *      Author: Gabriel Naves
 */

#include "../include/InputManager.h"

/**
 * Initializes the mouseState, quitGame,
 * mouseX, mouseY variables.
 */
InputManager::InputManager()
{
    for (int i = 0; i < N_MOUSE_BUTTONS; i++)
        mouseState[i] = RELEASED;
    quitGame = false;
    mouseX = 0, mouseY = 0;
}

InputManager::~InputManager(){}

InputManager& InputManager::GetInstance()
{
	/*Utilizes Meyers' Singleton*/
    static InputManager inputManager;
    return inputManager;
}

/**
 * Gets all the input events and manages the keyState map
 * and mouseState vector.
 */
void InputManager::Update()
{
    SDL_Event event;

    SDL_GetMouseState(&mouseX, &mouseY); //updates the coordinates of the mouse
    quitGame = false;
    //runs the map and sees which elements are pressed and released
    for (auto it = keyState.begin(); it != keyState.end(); ++it)
    {
        if (it->second == JUST_PRESSED)
            it->second = PRESSED;
        else if (it->second == JUST_RELEASED)
            it->second = RELEASED;
    }
    //does the same for the array
    for (int i = 0; i < N_MOUSE_BUTTONS; ++i)
    {
        if (mouseState[i] == JUST_PRESSED)
            mouseState[i] = PRESSED;
        else if (mouseState[i] == JUST_RELEASED)
            mouseState[i] = RELEASED;
    }

    //if there is an event yet to be processed, returns true and stores in event. else, returns false
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_QUIT:
                quitGame = true;
                break;
            case SDL_MOUSEBUTTONDOWN:
                mouseState[event.button.button] = JUST_PRESSED;
                break;
            case SDL_MOUSEBUTTONUP:
                mouseState[event.button.button] = JUST_RELEASED;
                break;
            case SDL_KEYDOWN:
                if (event.key.repeat) break; //so a pressed key will not behave as if it were pressed many times
                keyState[event.key.keysym.sym] = JUST_PRESSED;
                break;
            case SDL_KEYUP:
                keyState[event.key.keysym.sym] = JUST_RELEASED;
                break;
        }
    }
}

bool InputManager::KeyPress(int key)
{
    return (keyState[key] == JUST_PRESSED ? true : false);
}

bool InputManager::KeyRelease(int key)
{
    return (keyState[key] == JUST_RELEASED ? true : false);
}

bool InputManager::IsKeyDown(int key)
{
    return (keyState[key] == PRESSED ? true : false);
}

bool InputManager::MousePress(int button)
{
    return (mouseState[button] == JUST_PRESSED ? true : false);
}

bool InputManager::MouseRelease(int button)
{
    return (mouseState[button] == JUST_RELEASED ? true : false);
}

bool InputManager::IsMouseDown(int button)
{
    return (mouseState[button] == PRESSED ? true : false);
}

int InputManager::GetMouseX()
{
    return mouseX;
}

int InputManager::GetMouseY()
{
    return mouseY;
}

bool InputManager::IsMouseInside(Rect rect)
{
    return rect.IsInside(mouseX, mouseY);
}

bool InputManager::ShouldQuit()
{
    return quitGame;
}
