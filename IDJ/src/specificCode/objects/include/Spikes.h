/*
 * Spikes.h
 *
 *  Created on: Jun 10, 2014
 *      Author: icaro
 */

#ifndef SPIKES_H_
#define SPIKES_H_

#include "../../../Engine.h"
#include "../../characters/include/Loki.h"
#include "../../characters/include/Thor.h"

class Spikes : public GameObject
{
  public:
    Spikes(std::string spikes, int x, int y);
    virtual ~Spikes();
    void Render();
    void Update(float dt);
    bool Is(std::string type);
    void NotifyCollision(GameObject &other);
  private:
    Sprite spikesSp;
};

#endif /* SPIKES_H_ */
