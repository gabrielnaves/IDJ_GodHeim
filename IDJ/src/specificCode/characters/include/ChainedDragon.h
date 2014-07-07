/*
 * ChainedDragon.h
 *
 *  Created on: Jul 7, 2014
 *      Author: Gabriel Naves
 */

#ifndef CHAINEDDRAGON_H_
#define CHAINEDDRAGON_H_

#include "../../../Engine.h"
#include "../../objects/include/FloatingBlock.h"

namespace CDragon
{
    const float REST_TIME = 4;
    const float ATTACK_TIME = 1.3;
    const float FIREBALL_SPEED = 300;
    enum DragonState { RESTING, ATTACKING };
}

class ChainedDragon : public GameObject
{
  public:
    ChainedDragon(float x, float y, bool facingRight);
    ChainedDragon(FloatingBlock* block, bool facingRight);
    void Update(float dt);
    void Render();
    void NotifyCollision(GameObject& other);

    bool IsDead();
    bool Is(std::string type);

  private:
    void FollowBlock();
    void Rest(float dt);
    void Attack(float dt);

    Sprite attackSp, restSp;
    Timer restTimer, attackTimer;
    FloatingBlock *block;
    bool facingRight;
    CDragon::DragonState state;
};

#endif /* CHAINEDDRAGON_H_ */
