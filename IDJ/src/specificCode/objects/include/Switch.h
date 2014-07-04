/*
 * Switch.h
 *
 *  Created on: Jul 4, 2014
 *      Author: Gabriel Naves
 */

#ifndef SWITCH_H_
#define SWITCH_H_

#include "../../../Engine.h"
#include "../../characters/include/Barrier.h"

class Switch: public GameObject
{
  public:
    Switch(float x, float y, std::string initial, std::string final, GameObject* connectedObject);
    void Update(float dt);
    void Render();
    void NotifyCollision(GameObject& other);
    bool Is(std::string type);

  private:
    Sprite initialSprite, finalSprite;
    bool activated, thorColliding, lokiColliding;
    GameObject* connectedObject;
};

#endif /* SWITCH_H_ */
