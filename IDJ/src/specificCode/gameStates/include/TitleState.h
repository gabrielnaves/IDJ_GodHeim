/*
 * TitleState.h
 *
 *  Created on: Jun 6, 2014
 *      Author: icaro
 */

#ifndef TITLESTATE_H_
#define TITLESTATE_H_

#include "Level1State.h"
#include "../../../engine/include/Text.h"
#include "../../../engine/include/Sprite.h"
#include "../../objects/include/MenuBox.h"

class TitleState : public State
{
  public:
    TitleState();
    ~TitleState();
    void Update(float dt);
    void Render();

    void UpdateArray(float dt);

  private:
    Sprite bg;
};

#endif /* TITLESTATE_H_ */
