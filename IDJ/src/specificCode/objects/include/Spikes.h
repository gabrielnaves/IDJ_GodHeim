/*
 * Spikes.h
 *
 *  Created on: Jun 10, 2014
 *      Author: icaro
 */

#ifndef SPIKES_H_
#define SPIKES_H_

#include "../../../engine/include/GameObject.h"
#include "../../../engine/include/Camera.h"
#include "../../../engine/include/Sprite.h"

class Spikes : public GameObject
{
  public:
    Spikes(std::string spikes, int x, int y);
    virtual ~Spikes();
    void Update(float dt);
    void Render();
    void NotifyCollision(GameObject& other);
    bool IsDead();
    bool Is(std::string type);
  private:
    Sprite spikesSp;
};

#endif /* SPIKES_H_ */
