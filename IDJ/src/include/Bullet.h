/*
 * Bullet.h
 *
 *  Created on: Apr 26, 2014
 *      Author: Gabriel Naves
 */

#ifndef BULLET_H_
#define BULLET_H_

#include "GameObject.h"
#include "Sprite.h"

class Bullet: public GameObject
{
  public:
    Bullet(float x, float y, float angle, float speed, float maxDistance, Sprite sprite);
    void Update(float dt);
    void Render();
    bool IsDead();

  private:
    Sprite sp;
    Point speed;
    float distanceLeft;
};

#endif /* BULLET_H_ */
