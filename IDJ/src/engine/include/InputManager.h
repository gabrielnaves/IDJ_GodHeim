/*
 * InputManager.h
 *
 *  Created on: Apr 11, 2014
 *      Author: Gabriel Naves
 *
 *  Description: Class that manages inputs of the keyboard and mouse.
 *
 */

#ifndef INPUTMANAGER_H_
#define INPUTMANAGER_H_

#include <SDL.h>
#include <unordered_map>
#include <iostream>
#include <vector>

#include "Rect.h"

#define LEFT_ARROW_KEY      SDLK_LEFT
#define RIGHT_ARROW_KEY     SDLK_RIGHT
#define UP_ARROW_KEY        SDLK_UP
#define DOWN_ARROW_KEY      SDLK_DOWN
#define ESCAPE_KEY          SDLK_ESCAPE
#define SPACE_KEY           SDLK_SPACE
#define LEFT_MOUSE_BUTTON   SDL_BUTTON_LEFT
#define RIGHT_MOUSE_BUTTON  SDL_BUTTON_RIGHT
#define N_MOUSE_BUTTONS     5

class InputManager
{
  public:
    InputManager();
    virtual ~InputManager();

    void Update();

    bool KeyPress(int key);
    bool KeyRelease(int key);
    bool IsKeyDown(int key);

    bool MousePress(int button);
    bool MouseRelease(int button);
    bool IsMouseDown(int button);

    int GetMouseX();
    int GetMouseY();
    bool IsMouseInside(Rect rect);

    bool ShouldQuit();

    static InputManager& GetInstance();

  private:
    enum InputState
    {
        RELEASED = 0,
        JUST_RELEASED = 1,
        PRESSED = 2,
        JUST_PRESSED = 3
    };

    InputState mouseState[N_MOUSE_BUTTONS];
    std::unordered_map<int, InputState> keyState;

    bool quitGame;
    int mouseX, mouseY;
};

#endif /* INPUTMANAGER_H_ */
