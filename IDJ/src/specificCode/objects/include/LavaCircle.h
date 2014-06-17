/*
 * LavaCircle.h
 *
 *  Created on: Jun 17, 2014
 *      Author: Gabriel Naves
 */

#ifndef LAVACIRCLE_H_
#define LAVACIRCLE_H_

#include "../../../Engine.h"

class LavaCircle : public GameObject
{
  public:
    LavaCircle(float x, float y);
    ~LavaCircle();

    void Update(float dt);
    void Render();
    bool Is(std::string type);

  private:
    Sprite sp;
};

#endif /* LAVACIRCLE_H_ */
