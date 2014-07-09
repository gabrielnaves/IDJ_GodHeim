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

    SelectMusic();
    titleMusic.Play(-1);
    startEndTimer = false;

}

TitleState::~TitleState()
{
//    titleMusic.Stop();
}

void TitleState::Input()
{
	if (InputManager::GetInstance().ShouldQuit())
	        requestQuit = true;
//    if (InputManager::GetInstance().KeyPress(SDLK_1))
//    {
//    	titleMusic.Stop();
//    	StateData::soundMode = "Normal";
//    	SelectMusic();
//    	titleMusic.Play(-1);
//    }
//    if (InputManager::GetInstance().KeyPress(SDLK_2))
//    {
//    	titleMusic.Stop();
//    	StateData::soundMode = "8bits";
//    	SelectMusic();
//    	titleMusic.Play(-1);
//    }
//    if (InputManager::GetInstance().KeyPress(SDLK_3))
//    {
//    	titleMusic.Stop();
//    	StateData::soundMode = "SNES";
//    	SelectMusic();
//    	titleMusic.Play(-1);
//    }
}

void TitleState::Update(float dt)
{
    UpdateArray(dt);
    cursor.Update(dt);
    Input();
    if (startEndTimer) endTimer.Update(dt);
    if (endTimer.Get() >= 2.5)
    {
    	//        requestDelete = true;
    	endTimer.Restart();
    	startEndTimer = false;
    	if (clicked == "New Game")
    	{
    		Game::GetInstance().ResetWindowSize(1200,650);
    		Game::GetInstance().Push(SelectLevel());
    	}
    	else if (clicked == "Options")
    	{
    		Game::GetInstance().Push(new OptionsState());
    	}
    	else if (clicked == "Continue")
    	{
    		StateData::RetrieveCheckpoint();
    		Game::GetInstance().ResetWindowSize(1200,650);
    		Game::GetInstance().Push(SelectLevel());
    	}
    	clicked = "";
    }
}

/**
 * Selects the level that the player will start the game
 */
State* TitleState::SelectLevel()
{
    if (StateData::startingLevel == 1) return(new Level1State());
    if (StateData::startingLevel == 2) return(new Level2State());
    return NULL;
}

/**
 * Select the music according to the soundtrack mode
 */
void TitleState::SelectMusic()
{
    if (StateData::soundMode == "Normal")
        titleMusic.Open("audio/SOUNDTRACK MODE/Menu/Title.mp3");
    if (StateData::soundMode == "8bits")
        titleMusic.Open("audio/8 bit MODE/Title.mp3");
    if (StateData::soundMode == "SNES")
        titleMusic.Open("audio/Forever SNES MODE/Title.mp3");
}

void TitleState::Render()
{
    bg.Render(0,0);
    RenderArray();
    cursor.Render();
}

void TitleState::UpdateArray(float dt)
{
    for (int i = 0; i < (int)objectArray.size(); i++)
    {
        objectArray[i]->Update(dt);
        if (objectArray[i]->IsDead() && objectArray[i]->Is("Continue"))
        {
        	clicked = "Continue";
        	cursor.ChangeSp("img/menu/mouseThunder.png");
        	startEndTimer = true;
        	titleMusic.Stop(2.4);
        	objectArray[i]->Activate();
        }
        else if (objectArray[i]->IsDead() && objectArray[i]->Is("New Game"))
        {
        	clicked = "New Game";
            cursor.ChangeSp("img/menu/mouseThunder.png");
            startEndTimer = true;
            titleMusic.Stop(2.4);
            objectArray[i]->Activate();
        }
        else if (objectArray[i]->IsDead() && objectArray[i]->Is("Options"))
        {
        	clicked = "Options";
        	cursor.ChangeSp("img/menu/mouseThunder.png");
        	startEndTimer = true;
        	titleMusic.Stop(2.4);
        	objectArray[i]->Activate();
        }
    }
}
