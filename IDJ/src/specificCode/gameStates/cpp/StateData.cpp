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
Point StateData::lokiBox = Point();
Point StateData::thorBox = Point();

void StateData::CreateCheckPoint()
{
	StateData::lokiBox = Loki::characterLoki->box.GetPoint();
	StateData::thorBox = Thor::characterThor->box.GetPoint();
	StateData::checkpoint = true;
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

}

void StateData::RetrieveCheckpoint()
{

}

