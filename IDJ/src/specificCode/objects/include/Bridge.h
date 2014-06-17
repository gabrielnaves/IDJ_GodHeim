/*
 * Bridge.h
 *
 *  Created on: Jun 9, 2014
 *      Author: Gabriel Naves
 */

#ifndef BRIDGE_H_
#define BRIDGE_H_

#include "../../../Engine.h"
#include "../../characters/include/Barrier.h"

class Bridge : public GameObject
{
  public:
    Bridge(float x, float y);
    ~Bridge();

    void Update(float dt);
    void Render();
    void NotifyCollision(GameObject& other);

    bool Is(std::string type);

  private:
    float CheckPointPosition(Character* character, bool charAbove);
    void CharacterInside(Character* character);

    Sprite bridgeSp;
    std::vector<LineSegment> bridgeSegment;

    bool lokiColliding, thorColliding;
    bool lokiAbove, thorAbove;
};

#endif /* BRIDGE_H_ */
