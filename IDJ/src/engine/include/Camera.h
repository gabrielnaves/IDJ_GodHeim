/*
 * Camera.h
 *
 *  Created on: Apr 20, 2014
 *      Author: Gabriel Naves
 *
 *  Description: Class that determines the position of the camera in the game, as well as how fast it moves.
 *  			 Has the option of following an object, so the camera will always be fixed on it.
 *
 */

#ifndef CAMERA_H_
#define CAMERA_H_

#include <iostream>
#include <cmath>

#include "GameObject.h"
#include "InputManager.h"
#include "Game.h"

class Camera
{
  public:
    static Point pos;
    static float speed;
    static void Follow(GameObject* newFocus, bool isLimited = false,
                       float left=0, float upper=0, float right=0, float lower=0);
    static void SetLimit(float left, float upper, float right, float lower);
    static void Unfollow();
    static void Update(float dt);

  private:
    static GameObject* focus;
    static bool isLimited;
    static float upperLimit, lowerLimit;
    static float leftLimit, rightLimit;
};

#endif /* CAMERA_H_ */
