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

#include "../../../Engine.h"
#include "../../characters/include/Barrier.h"
#include "../../items/include/ItemFlags.h"

class StateData
{
  public:
    static int startingLevel;
    static std::string soundMode;
    static std::string controls;
    static bool unlockedLevel[10];
    static bool unlockedSound[4];
    static bool unlockedControls[3];
    static bool checkpoint;
    static bool haveDied;
    static Point lokiBox;
    static Point thorBox;

    static void CreateCheckPoint();
    static void SaveCheckpoint();
    static void RetrieveCheckpoint();
    static void UnlockLevel(int i);
    static void UnlockSound(int i);
};

#endif /* STATEDATA_H_ */
