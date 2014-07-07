/*
 * MenuBox.h
 *
 *  Created on: Jun 9, 2014
 *      Author: Gabriel Naves
 */

#ifndef MENUBOX_H_
#define MENUBOX_H_

#include "../../../Engine.h"

class MenuBox : public GameObject
{
  public:
    MenuBox(float x, float y, std::string spFile1, std::string spFile2, std::string type);

    void Update(float dt);
    void Render();

    bool IsDead();
    bool Is(std::string type);
    void Activate();

  private:
    Sprite sp1, sp2;
    bool isMouseInside, click;
    std::string type;
    Sound thunderSound, clickSound;
};

#endif /* MENUBOX_H_ */
