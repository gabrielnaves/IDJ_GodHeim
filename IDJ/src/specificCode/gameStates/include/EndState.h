/*
 * EndState.h
 *
 *  Created on: Jul 5, 2014
 *      Author: icaro
 */

#ifndef ENDSTATE_H_
#define ENDSTATE_H_

#include "../../../Engine.h"
#include "StateData.h"
#include "TitleState.h"

class EndState : public State
{
  public:
	EndState();
	void Update(float dt);
	void Render();
  private:
	void Input();
	std::vector<std::unique_ptr<Sprite>> bg;
	Music music;
	int bgCount, loopCounter;
	Timer timer;
};

#endif /* ENDSTATE_H_ */
