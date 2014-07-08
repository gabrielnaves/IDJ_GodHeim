/*
 * ArrowButton.h
 *
 *  Created on: Jul 8, 2014
 *      Author: arthur
 */

#ifndef ARROWBUTTON_H_
#define ARROWBUTTON_H_

#include "../../../Engine.h"
#include "OptionBox.h"
#include "../../gameStates/include/StateData.h"

class ArrowButton: public GameObject
{
   public:
	ArrowButton(float x, float y, bool increase, OptionBox* father);

	void Update(float dt);
	void Render();
	bool Is(std::string type);
	void Activate();
   private:
	Sprite sp, spClick;
	bool increase, isMouseInside, click;
	Sound clickSound;
	OptionBox* father;
};



#endif /* ARROWBUTTON_H_ */
