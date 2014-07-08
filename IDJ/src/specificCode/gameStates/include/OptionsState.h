/*
 * OptionsState.h
 *
 *  Created on: Jul 8, 2014
 *      Author: arthur
 */

#ifndef OPTIONSSTATE_H_
#define OPTIONSSTATE_H_

#include "../../../Engine.h"
#include "../../objects/include/MenuBox.h"
#include "../../objects/include/OptionBox.h"
#include "../../objects/include/Cursor.h"
#include "StateData.h"

class OptionsState: public State
{
   public:
	OptionsState();
	~OptionsState();
	void Update(float dt);
	void Render();

	void UpdateArray(float dt);
   private:
	Sprite bg;
	Cursor cursor;
	Timer endTimer;

	bool startEndTimer, canReturn;
};


#endif /* OPTIONSSTATE_H_ */
