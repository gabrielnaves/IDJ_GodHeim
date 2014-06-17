/*
 * Cursor.h
 *
 *  Created on: Jun 13, 2014
 *      Author: arthur
 */

#ifndef CURSOR_H_
#define CURSOR_H_

#include "../../../engine/include/InputManager.h"
#include "../../../engine/include/GameObject.h"
#include "../../../engine/include/Sprite.h"
#include "../../../engine/include/Camera.h"
#include "../../../engine/include/Timer.h"


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
