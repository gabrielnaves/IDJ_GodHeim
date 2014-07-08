/*
 * TitleState.h
 *
 *  Created on: Jun 6, 2014
 *      Author: icaro
 */

#ifndef TITLESTATE_H_
#define TITLESTATE_H_

#include "../../../Engine.h"
#include "../../objects/include/MenuBox.h"
#include "../../objects/include/Cursor.h"
#include "Level1State.h"
#include "Level2State.h"
#include "OptionsState.h"
#include "StateData.h"

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
    Cursor cursor;

    std::string clicked;
    bool startEndTimer;
    State* SelectLevel();
    void SelectMusic();
};

#endif /* TITLESTATE_H_ */
