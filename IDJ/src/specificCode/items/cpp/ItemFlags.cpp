/*
 * ItemFlags.cpp
 *
 *  Created on: Jun 30, 2014
 *      Author: icaro
 */

#include "../include/ItemFlags.h"

bool ItemFlags::fireBall = false;
bool ItemFlags::eagle = false;

void ItemFlags::ChangeFlag(std::string name, bool newValue)
{
    if (name == "LokiFire")
        fireBall = newValue;
    if (name == "LokiEagle")
        eagle = newValue;
    if (name == "ThorBelt")
        belt = newValue;
}
