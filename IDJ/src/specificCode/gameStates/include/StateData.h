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
};

#endif /* STATEDATA_H_ */
