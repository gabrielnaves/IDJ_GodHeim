/*
 * OptionBox.h
 *
 *  Created on: Jul 8, 2014
 *      Author: arthur
 */

#ifndef OPTIONBOX_H_
#define OPTIONBOX_H_

#include "../../../Engine.h"
#include "../../gameStates/include/StateData.h"

class OptionBox : public GameObject
{
   public:
	OptionBox(float x, float y, std::string type, int value);
	~OptionBox();

	void Update(float dt);
	void Render();
	bool Is(std::string type);

	void SetValue(int value);
	int GetValue();
   private:
	Sprite sp, spLock;
	std::string type;
	Music optionMusic;
	int value, newValue;
	GameObject* increaseButton, *decreaseButton;

	void ChangeStateDataMusic();
	void SelectMusic();
};



#endif /* OPTIONBOX_H_ */
