/*
 * Skeleton.h
 *
 *  Created on: Jul 7, 2014
 *      Author: icaro
 */

#ifndef SKELETON_H_
#define SKELETON_H_

#include "../../../Engine.h"
#include "../../characters/include/Character.h"
#include "../../characters/include/Barrier.h"

namespace SkeletonNamespace
{
	enum State {RESTING, WALKING};
	const float VISION_DISTANCE = 12*55;
}

class Skeleton : public GameObject
{
  public:
	Skeleton(float x, float y);
    void Update(float dt);
    void Render();
    void NotifyCollision(GameObject& other);
    bool IsDead();
    bool Is(std::string type);
  private:
    void Rest(float dt);
    void Walk(float dt);
    void MakeSound();
    void Attack(float dt);
    void SetState(SkeletonNamespace::State state);
    void Die();
    Rect FindClosestCharacter();
    int hp;
    bool facingRight;
    Sprite restSp, walkSp;
    Rect visionField;
    SkeletonNamespace::State state;
	float WALK_SPEED;
};

#endif /* SKELETON_H_ */
