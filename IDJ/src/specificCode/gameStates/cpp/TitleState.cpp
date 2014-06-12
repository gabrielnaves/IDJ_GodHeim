/*
 * TitleState.cpp
 *
 *  Created on: Jun 6, 2014
 *      Author: icaro
 */

#include "../include/TitleState.h"

TitleState::TitleState() : State()
{
    bg.Open("img/menu/menuBackground.png");

    AddObject(new MenuBox(210, 300, "img/menu/resume.png", "img/menu/resumeBold.png", "Continue"));
    AddObject(new MenuBox(210, 384, "img/menu/newGame.png", "img/menu/newGameBold.png", "New Game"));
    AddObject(new MenuBox(210, 470, "img/menu/options.png", "img/menu/optionsBold.png", "Options"));
}

TitleState::~TitleState()
{
    // TODO Auto-generated destructor stub
}

void TitleState::Update(float dt)
{
    UpdateArray(dt);
    if (InputManager::GetInstance().ShouldQuit())
        requestQuit = true;
}

void TitleState::Render()
{
    bg.Render(0,0);
    RenderArray();
}

void TitleState::UpdateArray(float dt)
{
    for (int i = 0; i < (int)objectArray.size(); i++)
    {
        objectArray[i]->Update(dt);
        if (objectArray[i]->IsDead() && objectArray[i]->Is("Continue"))
        {
        }
        else if (objectArray[i]->IsDead() && objectArray[i]->Is("New Game"))
        {
            Game::GetInstance().ResetWindowSize(1200,650);
            Game::GetInstance().Push(new Level1State());
        }
        else if (objectArray[i]->IsDead() && objectArray[i]->Is("Options"))
        {
        }
    }
}
