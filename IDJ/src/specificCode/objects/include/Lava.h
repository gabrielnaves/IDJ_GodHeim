/*
 * Lava.h
 *
 *  Created on: Jun 18, 2014
 *      Author: Gabriel Naves
 */

#ifndef LAVA_H_
#define LAVA_H_

#include "../../../Engine.h"
#include "../../characters/include/Thor.h"
#include "../../characters/include/Loki.h"

class Lava : public GameObject
{
  public:
    Lava(float x, float y);
    ~Lava();

    void Update(float dt);
    void Render();
    bool Is(std::string type);
    void NotifyCollision(GameObject &other);

  private:
    Sprite sp;
};

#endif /* LAVA_H_ */
