/*
 * OptionBox.cpp
 *
 *  Created on: Jul 8, 2014
 *      Author: arthur
 */

#include "../include/OptionBox.h"
#include "../include/ArrowButton.h"

OptionBox::OptionBox(float x, float y, std::string type, int value)
{
	std::string fileName;
	this->type = type;
	this->type = type;
	this->value = value;
	newValue = 0;
	if (type == "LevelOption")
	{
		fileName += "img/menu/level", fileName += std::to_string(value), fileName += ".png";
		sp.Open(fileName);
	}
	else if (type == "SoundOption")
	{
		fileName += "img/menu/music", fileName += std::to_string(value), fileName += ".png";
		sp.Open(fileName);
		SelectMusic();
	}
	else if (type == "ControlsOption")
	{
		fileName += "img/menu/newcontrols", fileName += std::to_string(value), fileName += ".png";
		sp.Open(fileName);
	}
	spLock.Open("img/menu/locked.png");
	box.Set(x, y, sp.GetWidth(), sp.GetHeight());

	increaseButton = (ArrowButton*) new ArrowButton(x + box.GetW() + 40, y + 10, true, this);
	decreaseButton = (ArrowButton*) new ArrowButton(x - 50, y + 10, false, this);
}

OptionBox::~OptionBox()
{
	delete increaseButton;
	delete decreaseButton;
}

void OptionBox::Update(float dt)
{
	std::string fileName;
	if (newValue > 0)
	{
		value = newValue, newValue = 0;
		if (type == "LevelOption")
		{
			fileName = "img/menu/level", fileName += std::to_string(value), fileName += ".png";
			sp.Open(fileName);
			StateData::startingLevel = value;
		}
		else if (type == "SoundOption")
		{
			fileName = "img/menu/music", fileName += std::to_string(value), fileName += ".png";
			sp.Open(fileName);
			ChangeStateDataMusic();
		}
		else if (type == "ControlsOption")
		{
			fileName = "img/menu/newcontrols", fileName += std::to_string(value), fileName += ".png";
			sp.Open(fileName);
			ChangeStateControls();
		}
	}
	increaseButton->Update(dt);
	decreaseButton->Update(dt);
}

void OptionBox::Render()
{
	sp.Render(box.GetX(), box.GetY());
	if (type == "LevelOption")
	{
		if (!StateData::unlockedLevel[value])
			spLock.Render(box.GetX(), box.GetY(), -10);
	}
	else if (type == "SoundOption")
	{
		if (!StateData::unlockedSound[value])
			spLock.Render(box.GetX(), box.GetY(), -10);
	}
	else if (type == "ControlsOption")
	{
		if (!StateData::unlockedControls[value])
			spLock.Render(box.GetX(), box.GetY(), -10);
	}
	increaseButton->Render();
	decreaseButton->Render();
}


bool OptionBox::Is(std::string type)
{
    return type == this->type ? true : false;
}

void OptionBox::SetValue(int value)
{
	this->newValue = value;
}

void OptionBox::SelectMusic()
{
	optionMusic.Stop();
	if (StateData::unlockedSound[value]){
		if (StateData::soundMode == "Normal")
			optionMusic.Open("audio/SOUNDTRACK MODE/Menu/Title.mp3");
		if (StateData::soundMode == "8bits")
			optionMusic.Open("audio/8 bit MODE/Title.mp3");
		if (StateData::soundMode == "SNES")
			optionMusic.Open("audio/Forever SNES MODE/Title.mp3");
		optionMusic.Play(-1);
	}
}

void OptionBox::ChangeStateDataMusic()
{
	if (value == 1)
		StateData::soundMode = "Normal";
	else if (value == 2)
		StateData::soundMode = "8bits";
	else if (value == 3)
		StateData::soundMode = "SNES";
	SelectMusic();
}

void OptionBox::ChangeStateControls()
{
	if (value == 1)
		StateData::controls = "Keyboard";
	else if (value == 2)
		StateData::controls = "Joystick";
}

int OptionBox::GetValue()
{
	return value;
}
