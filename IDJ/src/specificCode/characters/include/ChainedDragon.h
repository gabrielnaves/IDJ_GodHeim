/*
 * ChainedDragon.h
 *
 *  Created on: Jul 7, 2014
 *      Author: Gabriel Naves
 */

#ifndef CHAINEDDRAGON_H_
#define CHAINEDDRAGON_H_

#include "../../../Engine.h"

class ChainedDragon : public GameObject
{
  public:
    ChainedDragon(float x, float y);
    void Update(float dt);
    void Render();
    void NotifyCollision(GameObject& other);

    bool IsDead();
    bool Is(std::string type);

  private:
    Sprite sp;
    bool facingRight;

};

#endif /* CHAINEDDRAGON_H_ */
