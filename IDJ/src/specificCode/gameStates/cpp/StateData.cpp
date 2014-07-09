/*
 * StateData.cpp
 *
 *  Created on: Jul 3, 2014
 *      Author: icaro
 */

#include "../include/StateData.h"

int StateData::startingLevel = 1;
std::string StateData::soundMode = "Normal";
std::string StateData::controls = "Keyboard";
bool StateData::unlockedLevel[10] = {false, true, true, false, false, false, false, false, false, false};		//unlockedLevel[0]    NOT USED!!!!
bool StateData::unlockedSound[4] = {false, true, true, false};													//unlockedSound[0]    NOT USED!!!!
bool StateData::unlockedControls[3] = {false, true, false};														//unlockedControls[0] NOT USED!!!!
bool StateData::checkpoint = false;
bool StateData::haveDied = false;
Point StateData::lokiBox = Point();
Point StateData::thorBox = Point();

void StateData::CreateCheckPoint()
{
	StateData::lokiBox = Loki::characterLoki->box.GetPoint();
	StateData::thorBox = Thor::characterThor->box.GetPoint();
	StateData::checkpoint = true;
	StateData::haveDied = false;
}

void StateData::UnlockLevel(int i)
{
	StateData::unlockedLevel[i] = true;
}

void StateData::UnlockSound(int i)
{
	StateData::unlockedSound[i] = true;
}

void StateData::SaveCheckpoint()
{
	std::string line;
	std::ofstream stream("saveData.txt", std::ofstream::out | std::ofstream::trunc);

	stream << std::to_string(StateData::startingLevel) << std::endl;
	stream << StateData::soundMode << std::endl;
	stream << StateData::controls << std::endl;

	for (int i = 0; i < 10; i++)
	{
		if (StateData::unlockedLevel[i])
			stream << "true" << std::endl;
		else
			stream << "false" << std::endl;
	}

	for (int i = 0; i < 4; i++)
	{
		if (StateData::unlockedSound[i])
			stream << "true" << std::endl;
		else
			stream << "false" << std::endl;
	}

	for (int i = 0; i < 3; i++)
	{
		if (StateData::unlockedControls[i])
			stream << "true" << std::endl;
		else
			stream << "false" << std::endl;
	}

	if (StateData::checkpoint)
			stream << "true" << std::endl;
		else
			stream << "false" << std::endl;

	if (StateData::haveDied)
		stream << "true" << std::endl;
	else
		stream << "false" << std::endl;

	stream << std::to_string(StateData::lokiBox.GetX()) << std::endl;
	stream << std::to_string(StateData::lokiBox.GetY()) << std::endl;
	stream << std::to_string(StateData::thorBox.GetX()) << std::endl;
	stream << std::to_string(StateData::thorBox.GetY()) << std::endl;

	if (ItemFlags::fireBall)
		stream << "true" << std::endl;
	else
		stream << "false" << std::endl;

	if (ItemFlags::eagle)
		stream << "true" << std::endl;
	else
		stream << "false" << std::endl;

	if (ItemFlags::shield)
		stream << "true" << std::endl;
	else
		stream << "false" << std::endl;

	if (ItemFlags::belt)
		stream << "true" << std::endl;
	else
		stream << "false" << std::endl;

	if (ItemFlags::hammer)
		stream << "true" << std::endl;
	else
		stream << "false" << std::endl;

	if (ItemFlags::redPotion)
		stream << "true" << std::endl;
	else
		stream << "false" << std::endl;



	stream.close();
}

void StateData::RetrieveCheckpoint()
{
	std::string line;
	std::ifstream stream("saveData.txt");
	if (!stream.fail())
	{
		std::getline(stream, line);
		StateData::startingLevel = std::stoi(line);

		std::getline(stream, line);
		StateData::soundMode = line;

		std::getline(stream, line);
		StateData::controls = line;

		for (int i = 0; i < 10; i++)
		{
			std::getline(stream, line);
			if (line == "true")
				StateData::unlockedLevel[i] = true;
			else
				StateData::unlockedLevel[i] = false;
		}

		for (int i = 0; i < 4; i++)
		{
			std::getline(stream, line);
			if (line == "true")
				StateData::unlockedSound[i] = true;
			else
				StateData::unlockedSound[i] = false;
		}

		for (int i = 0; i < 3; i++)
		{
			std::getline(stream, line);
			if (line == "true")
				StateData::unlockedControls[i] = true;
			else
				StateData::unlockedControls[i] = false;
		}

		std::getline(stream, line);
		if (line == "true")
			StateData::checkpoint = true;
		else
			StateData::checkpoint = false;

		std::getline(stream, line);
		if (line == "true")
			StateData::haveDied = true;
		else
			StateData::haveDied = false;

		std::getline(stream, line);
		StateData::lokiBox.Set(stof(line), 0);
		std::getline(stream, line);
		StateData::lokiBox.Set(StateData::lokiBox.GetX(), stof(line));

		std::getline(stream, line);
		StateData::thorBox.Set(stof(line), 0);
		std::getline(stream, line);
		StateData::thorBox.Set(StateData::thorBox.GetX(), stof(line));


		//ItemFlags

		std::getline(stream, line);
		if (line == "true")
			ItemFlags::fireBall = true;
		else
			ItemFlags::fireBall = false;

		std::getline(stream, line);
		if (line == "true")
			ItemFlags::eagle = true;
		else
			ItemFlags::eagle = false;

		std::getline(stream, line);
		if (line == "true")
			ItemFlags::shield = true;
		else
			ItemFlags::shield = false;

		std::getline(stream, line);
		if (line == "true")
			ItemFlags::belt = true;
		else
			ItemFlags::belt = false;

		std::getline(stream, line);
		if (line == "true")
			ItemFlags::hammer = true;
		else
			ItemFlags::hammer = false;

		std::getline(stream, line);
		if (line == "true")
			ItemFlags::redPotion = true;
		else
			ItemFlags::redPotion = false;

		stream.close();
	}
}

