/*
 * Geyser.h
 *
 *  Created on: Jul 7, 2014
 *      Author: Gabriel Naves
 */

#ifndef GEYSER_H_
#define GEYSER_H_

#include "../../../Engine.h"

namespace GeyserNamespace
{
    enum GeyserState { ACTIVE, INACTIVE, ACTIVATING, DEACTIVATING };
}

class Geyser: public GameObject
{
  public:
    Geyser(float x, float y);
    void Update(float dt);
    void Render();
    void NotifyCollision(GameObject& other);

    bool IsDead();
    bool Is(std::string type);

  private:
    void UpdateInactive(float dt);
    void ActivateGeyser(float dt);
    void UpdateActive(float dt);
    void Deactivate(float dt);

    Rect renderingBox;
    Timer timer;
    Sprite inactive, active, activating;
    GeyserNamespace::GeyserState state;
};

#endif /* GEYSER_H_ */
