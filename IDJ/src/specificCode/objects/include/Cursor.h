/*
 * Cursor.h
 *
 *  Created on: Jun 13, 2014
 *      Author: arthur
 */

#ifndef CURSOR_H_
#define CURSOR_H_

#include "../../../Engine.h"


class Cursor: public GameObject
{
  public:
	Cursor();
	void Update(float dt);
	void Render();
	bool Is(std::string type);
  private:
	Sprite sp;
	Timer timer;
	bool click;

	const float CLICK_TIME = 0.2;
};


#endif /* CURSOR_H_ */
