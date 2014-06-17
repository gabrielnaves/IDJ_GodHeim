/*
 * Plants.h
 *
 *  Created on: Jun 9, 2014
 *      Author: icaro
 */

#ifndef PLANTS_H_
#define PLANTS_H_

#include "../../../Engine.h"

class Plants : public GameObject
{
  public:
    Plants(std::string plant, int x, int y);
    virtual ~Plants();
    void Render();
    void Update(float dt);
    bool Is(std::string type);
  private:
    Sprite plantSp;
};

#endif /* PLANTS_H_ */
