/*
 * TitleState.cpp
 *
 *  Created on: Jun 6, 2014
 *      Author: icaro
 */

#include "../include/TitleState.h"

TitleState::TitleState() : State()
{
    bg.Open("img/Opening.jpg");
    startOption.Set(150,350,280,75);
    newGameOption.Set(150,430,280,75);
    optionsOption.Set(150,510,280,75);
}

TitleState::~TitleState()
{
    // TODO Auto-generated destructor stub
}

void TitleState::Update(float dt)
{
    Input();
}

void TitleState::Render()
{
    bg.Render(0,0);
}

void TitleState::Input()
{
    InputManager &input = InputManager::GetInstance();

    if (input.MousePress(LEFT_MOUSE_BUTTON))
    {
        if (input.IsMouseInside(startOption)) //continues a saved game
        {
        }
        if (input.IsMouseInside(newGameOption)) //starts a new game
        {
            Game::GetInstance().ResetWindowSize(1200,650);
            Game::GetInstance().Push(new Level1State());
        }
        if (input.IsMouseInside(optionsOption)) //opens an option menu
        {

        }
    }
    if (input.ShouldQuit())
        requestQuit = true;
}
