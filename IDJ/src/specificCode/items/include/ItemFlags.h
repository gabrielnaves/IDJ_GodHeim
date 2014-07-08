/*
 * ItemFlags.h
 *
 *  Created on: Jun 30, 2014
 *      Author: icaro
 *
 *  Description:
 */

#ifndef ITEMFLAGS_H_
#define ITEMFLAGS_H_

#include "iostream"

class ItemFlags
{
  public:
    static bool fireBall;
    static bool eagle;
    static bool belt;
    static bool hammer;
    static bool redPotion;
    static void ChangeFlag(std::string name, bool newValue);
};

#endif /* ITEMFLAGS_H_ */
