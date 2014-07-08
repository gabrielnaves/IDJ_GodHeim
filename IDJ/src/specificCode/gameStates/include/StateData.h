/*
 * StateData.h
 *
 *  Created on: May 4, 2014
 *      Author: Gabriel Naves
 *              Icaro Mota
 *  Description: Has the information that must be shared between states.
 *
 */

#ifndef STATEDATA_H_
#define STATEDATA_H_

#include "iostream"

class StateData
{
  public:
    static int startingLevel;
    static std::string soundMode;
    static std::string controls;
    static bool unlockedLevel[10];
    static bool unlockedSound[4];
    static bool unlockedControls[3];
};

#endif /* STATEDATA_H_ */
