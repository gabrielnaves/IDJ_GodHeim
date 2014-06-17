/*
 * BrokenHouseBack.h
 *
 *  Created on: Jun 17, 2014
 *      Author: Gabriel Naves
 */

#ifndef BROKENHOUSEBACK_H_
#define BROKENHOUSEBACK_H_

#include "../../../Engine.h"

class BrokenHouseBack : public GameObject
{
  public:
    BrokenHouseBack(float x, float y);
    ~BrokenHouseBack();

    void Update(float dt);
    void Render();
    bool Is(std::string type);

  private:
    Sprite sp;
};

#endif /* BROKENHOUSEBACK_H_ */
