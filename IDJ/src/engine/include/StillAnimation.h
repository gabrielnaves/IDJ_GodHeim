/*
 * StillAnimation.h
 *
 *  Created on: May 2, 2014
 *      Author: Gabriel Naves
 *
 *  Description: Executes an animation without interacting with other objects
 *
 */

#ifndef STILLANIMATION_H_
#define STILLANIMATION_H_

#include "GameObject.h"
#include "Sprite.h"
#include "Camera.h"
#include "Timer.h"

class StillAnimation : public GameObject
{
  public:
    StillAnimation(float x, float y, float rotation, Sprite sprite, float timeLimit, bool ends);
    void Update(float dt);
    void Render();
    bool IsDead();
    void NotifyCollision(GameObject& other);
    bool Is(std::string type);

  private:
    Timer endTimer;
    float timeLimit;
    bool oneTimeOnly;
    Sprite sp;
};

#endif /* STILLANIMATION_H_ */
