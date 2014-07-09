/*
 * StateData.cpp
 *
 *  Created on: Jul 3, 2014
 *      Author: icaro
 */

#include "../include/StateData.h"

int StateData::startingLevel = 2;
std::string StateData::soundMode = "Normal";
std::string StateData::controls = "Keyboard";
bool StateData::unlockedLevel[10] = {false, true, true, false, false, false, false, false, false, false};		//unlockedLevel[0]    NOT USED!!!!
bool StateData::unlockedSound[4] = {false, true, true, false};													//unlockedSound[0]    NOT USED!!!!
bool StateData::unlockedControls[3] = {false, true, false};														//unlockedControls[0] NOT USED!!!!
