/*
 * EndState.cpp
 *
 *  Created on: Jul 5, 2014
 *      Author: icaro
 */

#include "../include/EndState.h"

EndState::EndState() : State()
{
	bg.emplace_back(new Sprite("img/gameover/gameover1.png"));
	bg.emplace_back(new Sprite("img/gameover/gameover2.png"));
	bg.emplace_back(new Sprite("img/gameover/gameover3.png"));
	bg.emplace_back(new Sprite("img/gameover/gameover2.png"));
	bgCount = loopCounter = 0;
}

void EndState::Update(float dt)
{
	Input();
	timer.Update(dt);
	if (timer.Get()>=0.5)
	{
		loopCounter++;
		bgCount ++;
		timer.Restart();
	}
	if (bgCount == (int)bg.size()) bgCount = 0;
	if (loopCounter >= 16)
	{
		requestDelete = true;
		Game::GetInstance().ResetWindowSize(574,600);
		Game::GetInstance().Push(new TitleState());
	}
}

void EndState::Render()
{
	bg[bgCount]->Render(0,0);
}

void EndState::Input()
{
    if (InputManager::GetInstance().ShouldQuit())
        requestQuit = true;
}
