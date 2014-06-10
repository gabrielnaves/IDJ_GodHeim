/*
 * Stairs.h
 *
 *  Created on: Jun 8, 2014
 *      Author: Gabriel Naves
 */

#ifndef STAIRS_H_
#define STAIRS_H_

#include "../../../engine/include/GameObject.h"
#include "../../../engine/include/Camera.h"
#include "../../../engine/include/Sprite.h"
#include "../../characters/include/Loki.h"
#include "../../characters/include/Thor.h"

class Stairs: public GameObject
{
  public:
    Stairs();
    virtual ~Stairs();
    void Update(float dt);
    void Render();
    void NotifyCollision(GameObject& other);
    bool IsDead();
    bool Is(std::string type);
  private:
    void LookForCharacterAbove(Character *character);
    Sprite stairsSp;
};

#endif /* STAIRS_H_ */
