/*
 * EndState.cpp
 *
 *  Created on: Jul 5, 2014
 *      Author: icaro
 */

#include "../include/EndState.h"

EndState::EndState() : State()
{
	bg.emplace_back(new Sprite("img/gameover/gameoverefeito1.png"));
	bg.emplace_back(new Sprite("img/gameover/gameoverefeito2.png"));
	bg.emplace_back(new Sprite("img/gameover/gameoverefeito3.png"));
	bg.emplace_back(new Sprite("img/gameover/gameoverefeito4.png"));
	bg.emplace_back(new Sprite("img/gameover/gameoverefeito5.png"));
	bg.emplace_back(new Sprite("img/gameover/gameoverefeito6.png"));
	bg.emplace_back(new Sprite("img/gameover/gameoverefeito7.png"));
	bg.emplace_back(new Sprite("img/gameover/gameoverefeito8.png"));
	bg.emplace_back(new Sprite("img/gameover/gameoverefeito9.png"));
	bg.emplace_back(new Sprite("img/gameover/gameoverefeito10.png"));
	bg.emplace_back(new Sprite("img/gameover/gameoverefeito11.png"));
	bg.emplace_back(new Sprite("img/gameover/gameover1.png"));
	bg.emplace_back(new Sprite("img/gameover/gameover2.png"));
	bg.emplace_back(new Sprite("img/gameover/gameover3.png"));
	bg.emplace_back(new Sprite("img/gameover/gameover2.png"));
	bg.emplace_back(new Sprite("img/gameover/gameover1.png"));
	bg.emplace_back(new Sprite("img/gameover/gameover2.png"));
    bg.emplace_back(new Sprite("img/gameover/gameover3.png"));
    bg.emplace_back(new Sprite("img/gameover/gameover2.png"));
    bg.emplace_back(new Sprite("img/gameover/gameover1.png"));
    bg.emplace_back(new Sprite("img/gameover/gameover2.png"));
    bg.emplace_back(new Sprite("img/gameover/gameover3.png"));
    bg.emplace_back(new Sprite("img/gameover/gameover2.png"));
    bg.emplace_back(new Sprite("img/gameover/gameover1.png"));
	bgCount = loopCounter = 0;
	music.Open("audio/GAME OVER.mp3");
	music.Play(-1);
}

void EndState::Update(float dt)
{
	Input();
	timer.Update(dt);
	if (timer.Get()>=0.15)
	{
		loopCounter++;
		bgCount ++;
		timer.Restart();
	}
	if (bgCount == (int)bg.size()) bgCount = 0;
	if (loopCounter >= (int)bg.size())
	{
		requestDelete = true;
		StateData::haveDied = false;
//		requestQuit = true;
//		Game::GetInstance().ResetWindowSize(1200,650);
//		Game::GetInstance().ResetWindowSize(574,600);
//		Game::GetInstance().Push(new TitleState());
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
