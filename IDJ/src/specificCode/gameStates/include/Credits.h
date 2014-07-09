/*
 * Credits.h
 *
 *  Created on: Jul 8, 2014
 *      Author: Gabriel Naves
 */

#ifndef CREDITS_H_
#define CREDITS_H_

#include "../../../Engine.h"
#include "TitleState.h"

class Credits: public State
{
  public:
    Credits();
    void Update(float dt);
    void Render();

  private:
    Sprite sp;
    Music music;
};

#endif /* CREDITS_H_ */
