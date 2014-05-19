/*
 * Camera.h
 *
 *  Created on: Apr 20, 2014
 *      Author: Gabriel Naves
 */

#ifndef CAMERA_H_
#define CAMERA_H_

#include <iostream>
#include <cmath>

#include "GameObject.h"
#include "InputManager.h"

class Camera
{
  public:
    static Point pos;
    static float speed;
    static void Follow(GameObject* newFocus);
    static void Unfollow();
    static void Update(float dt);

  private:
    static GameObject* focus;
};

#endif /* CAMERA_H_ */
