/*
 * Portal.h
 *
 *  Created on: Jul 8, 2014
 *      Author: Gabriel Naves
 */

#ifndef PORTAL_H_
#define PORTAL_H_

#include "../../../Engine.h"
#include "../../items/include/ItemFlags.h"

class Portal: public GameObject
{
  public:
    Portal(float x, float y);
    void Update(float dt);
    void Render();
    void NotifyCollision(GameObject& other);
    bool Is(std::string type);

  private:
    Sprite inactiveSp, activeSp;
    bool active;
};

#endif /* PORTAL_H_ */
