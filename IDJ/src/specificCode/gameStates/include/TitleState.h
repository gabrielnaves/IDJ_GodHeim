/*
 * TitleState.h
 *
 *  Created on: Jun 6, 2014
 *      Author: icaro
 */

#ifndef TITLESTATE_H_
#define TITLESTATE_H_

#include "../../../engine/include/Text.h"
#include "../../../engine/include/Sprite.h"
#include "../../../engine/include/Sound.h"
#include "../../objects/include/MenuBox.h"
#include "Level1State.h"

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
    Music titleMusic;
    Timer endTimer;

    bool startEndTimer;
};

#endif /* TITLESTATE_H_ */
