/*
 * Rock.h
 *
 *  Created on: Jul 5, 2014
 *      Author: icaro
 */

#ifndef ROCK_H_
#define ROCK_H_

#include "../../../Engine.h"
#include "../../characters/include/Loki.h"
#include "../../characters/include/Thor.h"

class Rock : public GameObject
{
  public:
	Rock(std::string sprite,float x, float y);
    void Update(float dt);
    void Render();
    void NotifyCollision(GameObject& other);

    bool Is(std::string type);
    bool IsDead();
  private:
    void InteractsWith(Character *character);
    void Die();
    Sprite sp;
    bool broke;
};

#endif /* ROCK_H_ */
