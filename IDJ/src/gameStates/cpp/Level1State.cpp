/*
 * Level1State.cpp
 *
 *  Created on: May 19, 2014
 *      Author: Gabriel Naves
 */

#include "../include/Level1State.h"

Level1State::Level1State() : State()
{
	bg.Open("img/background primeira fase tamanho total.png");
}

Level1State::~Level1State()
{
	// TODO Auto-generated destructor stub
}

void Level1State::Update(float dt)
{
	Camera::Update(dt);
	Input();
	UpdateArray(dt);
}

void Level1State::Render()
{
	bg.Render(-Camera::pos.GetX(),-Camera::pos.GetY());
	RenderArray();
}

void Level1State::Input()
{
	if (InputManager::GetInstance().ShouldQuit() || InputManager::GetInstance().KeyPress(ESCAPE_KEY))
		requestQuit = true;
}
