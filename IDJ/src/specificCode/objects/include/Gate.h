/*
 * Gate.h
 *
 *  Created on: Jul 6, 2014
 *      Author: icaro
 */

#ifndef GATE_H_
#define GATE_H_

#include "../../../Engine.h"
#include "../../characters/include/Loki.h"
#include "../../characters/include/Thor.h"
#include <cmath>

class Gate : public GameObject
{
  public:
    Gate(std::string gateSp, int x, int y);
    void Update(float dt);
    void Render();
    void NotifyCollision(GameObject& other);
    bool Is(std::string type);
  private:
    void InteractsWith(Character *character);
    bool ShouldStandOnStairs(Character *character);
    void Stand(Character *character);
    bool IsActive();
    bool IsCloseTo(Character *character);
    void UpdateSprite(float dt);
    bool CanClimb(Character *character);
    bool ShouldDrop(Character *character);
    void Drop(Character *character);
    Sprite gateSp;
    bool active;
    Rect prevThor;
    Rect prevLoki;
};

#endif /* GATE_H_ */
