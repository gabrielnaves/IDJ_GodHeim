/*
 * OptionsState.cpp
 *
 *  Created on: Jul 8, 2014
 *      Author: arthur
 */

#include "../include/OptionsState.h"

OptionsState::OptionsState()
{
	int sound = 0;
	if (StateData::soundMode == "Normal")
		sound = 1;
	else if (StateData::soundMode == "8bits")
		sound = 2;
	else
		sound = 3;

	bg.Open("img/menu/optionsBkg.png");

	AddObject(new OptionBox(230, 300, "LevelOption", StateData::startingLevel));
	AddObject(new OptionBox(230, 384, "SoundOption", sound));
	AddObject(new MenuBox(210, 470, "img/menu/options.png", "img/menu/optionsBold.png", "Options"));

	startEndTimer = false;
}

OptionsState::~OptionsState()
{
}

void OptionsState::Update(float dt)
{
	UpdateArray(dt);
	cursor.Update(dt);
	if (InputManager::GetInstance().ShouldQuit())
		requestQuit = true;
	if (startEndTimer) endTimer.Update(dt);
	if (endTimer.Get() >= 2.5)
		requestDelete = true;
}

void OptionsState::Render()
{
    bg.Render(0,0);
    RenderArray();
    cursor.Render();
}




