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

namespace WolfState
{
    enum WolfState { RESTING, RUNNING, ATTACKING, RETURNING };
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
    void Rest(float dt);
    void Run(float dt);
    void Attack(float dt);
    void Return(float dt);
    Rect FindClosestCharacter();

    float distance;
    int hp;
    bool facingRight, attacking;
    Sprite restSp, runSp, attackSp, walkSp;
    WolfState::WolfState state;
};

#endif /* WOLF_H_ */
