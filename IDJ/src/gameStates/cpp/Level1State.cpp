/*
 * Level1State.cpp
 *
 *  Created on: May 19, 2014
 *      Author: Gabriel Naves
 */

#include "../include/Level1State.h"

Level1State::Level1State() : State()
{
	bg.Open("img/background.png");
}

Level1State::~Level1State()
{
	// TODO Auto-generated destructor stub
}

void Level1State::Update(float dt)
{
	Camera::Update(dt);
	Input();
}

void Level1State::Render()
{
	bg.Render(0,0);
}

void Level1State::Input()
{
	if (InputManager::GetInstance().ShouldQuit())
		requestQuit = true;
}
