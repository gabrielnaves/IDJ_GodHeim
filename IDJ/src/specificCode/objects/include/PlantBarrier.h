/*
 * PlantBarrier.h
 *
 *  Created on: Jul 5, 2014
 *      Author: icaro
 */

#ifndef PLANTBARRIER_H_
#define PLANTBARRIER_H_

#include "../../../Engine.h"
#include "../../characters/include/Loki.h"
#include "../../characters/include/Thor.h"

class PlantBarrier : public GameObject
{
  public:
	PlantBarrier(std::string sprite,float x, float y);
    void Update(float dt);
    void Render();
    void NotifyCollision(GameObject& other);

    bool Is(std::string type);
    bool IsDead();
  private:
    void CollidesWith(Character *character);
    void Die();
    Sprite sp;
    float blockHeight;
    bool dead;
};

#endif /* PLANTBARRIER_H_ */
