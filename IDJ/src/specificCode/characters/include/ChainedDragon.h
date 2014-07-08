/*
 * ChainedDragon.h
 *
 *  Created on: Jul 7, 2014
 *      Author: Gabriel Naves
 */

#ifndef CHAINEDDRAGON_H_
#define CHAINEDDRAGON_H_

#include "../../../Engine.h"
#include "Bullet.h"
#include "../../objects/include/FloatingBlock.h"

namespace CDragon
{
    const float REST_TIME = 2;
    const float ATTACK_TIME = 1.3;
    const float FIREBALL_SPEED = 300;
    const float VISION_DISTANCE = 5000;
    enum DragonState { RESTING, ATTACKING };
}

class ChainedDragon : public GameObject
{
  public:
    ChainedDragon(float x, float y, bool facingRight, MovementMap movMap);
    ChainedDragon(FloatingBlock* block, bool facingRight, MovementMap movMap);
    void Update(float dt);
    void Render();
    void NotifyCollision(GameObject& other);

    bool IsDead();
    bool Is(std::string type);

  private:
    void FollowBlock();
    void Rest(float dt);
    void Attack(float dt);
    void Shoot();

    Sprite attackSp, restSp;
    Timer restTimer, attackTimer;
    FloatingBlock *block;
    bool facingRight;
    CDragon::DragonState state;
    Rect visionField;
    MovementMap movementMap;
};

#endif /* CHAINEDDRAGON_H_ */
