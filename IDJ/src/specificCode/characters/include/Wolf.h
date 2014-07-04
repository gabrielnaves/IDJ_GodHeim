/*
 * Wolf.h
 *
 *  Created on: Jun 29, 2014
 *      Author: Gabriel Naves
 */

#ifndef WOLF_H_
#define WOLF_H_

#include "../../../Engine.h"
#include "Character.h"
#include "Barrier.h"

namespace WolfNamespace
{
    const float RUN_SPEED = 200;
    const float WALK_SPEED = 100;
    const float ATTACK_SPEED = 300;
    const float HOLD_SPEED = 0;
    const float HOLD_DISTANCE = 200;
    enum WolfState { RESTING, RUNNING,
                     ATTACKING, RETURNING,
                     GET_UP, LIE_DOWN,
                     BEING_HELD };
}

class Wolf : public GameObject
{
  public:
    Wolf(float x, float y, float visionDistance, bool facingRight = true);
    ~Wolf();
    void Update(float dt);
    void Render();
    void NotifyCollision(GameObject& other);
    bool IsDead();
    bool Is(std::string type);

  private:
    void CheckIfWolfCanBeHeld();
    void CheckIfBeingHeld();
    void Rest(float dt);
    void GetUp(float dt);
    void Run(float dt);
    void Attack(float dt);
    void Return(float dt);
    void LieDown(float dt);
    void BeHeld(float dt);
    Rect FindClosestCharacter();

    int hp;
    bool facingRight, initialSideRight, dealtDamage;
    Sprite restSp, runSp, attackSp, walkSp, getUpSp, lieDownSp, heldSp;
    Rect visionField;
    Point initialPos;
    Timer attackTimer, getUpTimer, lieDownTimer, heldTimer;
    WolfNamespace::WolfState state;
};

#endif /* WOLF_H_ */
