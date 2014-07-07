/*
 * Rope.h
 *
 *  Created on: Jul 4, 2014
 *      Author: icaro
 */

#ifndef ROPE_H_
#define ROPE_H_

#include "../../../Engine.h"
#include "../../characters/include/Loki.h"
#include "../../characters/include/Thor.h"
#include <cmath>

class Rope : public GameObject
{
  public:
    Rope(std::string rope, int x, int y, bool active = true, int frameCount = 1, float frameTime = 1);
    void Update(float dt);
    void Render();
    void NotifyCollision(GameObject& other);
    bool Is(std::string type);
    void Activate();

  private:
    bool active;
    void Drop(Character *character);
    Sprite ropeSp;
    bool thorClimbing,lokiClimbing;
};

#endif /* ROPE_H_ */
