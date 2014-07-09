/*
 * OptionsState.cpp
 *
 *  Created on: Jul 8, 2014
 *      Author: arthur
 */

#include "../include/OptionsState.h"

OptionsState::OptionsState()
{
	int sound = 0, control = 0;
	if (StateData::soundMode == "Normal")
		sound = 1;
	else if (StateData::soundMode == "8bits")
		sound = 2;
	else
		sound = 3;

	if (StateData::controls == "Keyboard")
		control = 1;
	else if (StateData::controls == "Joystick")
		control = 2;

	bg.Open("img/menu/optionsBkg.png");

	AddObject(new OptionBox(230, 300, "LevelOption", StateData::startingLevel));
	AddObject(new OptionBox(230, 384, "SoundOption", sound));
	AddObject(new OptionBox(230, 470, "ControlsOption", control));
	AddObject(new MenuBox(500, 500, "img/menu/return.png", "img/menu/return2.png", "Return"));

	endTimer.Restart();
	startEndTimer = false;
	canReturn = true;
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

void OptionsState::UpdateArray(float dt)
{
	OptionBox* option = NULL;
	canReturn = true;
	for (int i = 0; i < (int)objectArray.size(); i++)
	{
		objectArray[i]->Update(dt);
		if (objectArray[i]->IsDead() && objectArray[i]->Is("Return"))
		{
			for(int j = 0; j < (int)objectArray.size(); j++)
			{
				if (objectArray[j]->Is("LevelOption"))
				{
					option = (OptionBox*) objectArray[j].get();
					if (!StateData::unlockedLevel[option->GetValue()])
					{
						canReturn = false;
					}
				}
				else if (objectArray[j]->Is("SoundOption"))
				{
					option = (OptionBox*) objectArray[j].get();
					if (!StateData::unlockedSound[option->GetValue()])
					{
						canReturn = false;
					}
				}
				else if (objectArray[j]->Is("ControlsOption"))
				{
					option = (OptionBox*) objectArray[j].get();
					if (!StateData::unlockedSound[option->GetValue()])
					{
						canReturn = false;
					}
				}
			}
			if (canReturn)
			{
				cursor.ChangeSp("img/menu/mouseThunder.png");
				canReturn = false;
				startEndTimer = true;
			}
			objectArray[i]->Activate();
		}
	}
}


