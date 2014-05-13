/*
 * InputManager.cpp
 *
 *  Created on: Apr 11, 2014
 *      Author: Gabriel Naves
 */

#include "../include/InputManager.h"

InputManager::InputManager()
{
    for (int i = 0; i < N_MOUSE_BUTTONS; i++)
    {
        mouseState[i] = RELEASED;
    }
    quitGame = false;
    mouseX = 0, mouseY = 0;
}

InputManager::~InputManager(){}

InputManager& InputManager::GetInstance()
{
    static InputManager inputManager;
    return inputManager;
}

void InputManager::Update()
{
    SDL_Event event;

    SDL_GetMouseState(&mouseX, &mouseY);
    quitGame = false;
    for (auto it = keyState.begin(); it != keyState.end(); ++it)
    {
        if (it->second == JUST_PRESSED)
            it->second = PRESSED;
        else if (it->second == JUST_RELEASED)
            it->second = RELEASED;
    }

    for (int i = 0; i < N_MOUSE_BUTTONS; ++i)
    {
        if (mouseState[i] == JUST_PRESSED)
            mouseState[i] = PRESSED;
        else if (mouseState[i] == JUST_RELEASED)
            mouseState[i] = RELEASED;
    }

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
                if (event.key.repeat) break;
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
