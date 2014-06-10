/*
 * Plants.h
 *
 *  Created on: Jun 9, 2014
 *      Author: icaro
 */

#ifndef PLANTS_H_
#define PLANTS_H_

#include "../../../engine/include/GameObject.h"
#include "../../../engine/include/Camera.h"
#include "../../../engine/include/Sprite.h"

class Plants : public GameObject
{
  public:
    Plants(std::string plant, int x, int y);
    virtual ~Plants();
    void Update(float dt);
    void Render();
    void NotifyCollision(GameObject& other);
    bool IsDead();
    bool Is(std::string type);
  private:
    Sprite plantSp;
};

#endif /* PLANTS_H_ */
