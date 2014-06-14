/*
 * MenuBox.h
 *
 *  Created on: Jun 9, 2014
 *      Author: Gabriel Naves
 */

#ifndef MENUBOX_H_
#define MENUBOX_H_

#include "../../../engine/include/GameObject.h"
#include "../../../engine/include/Camera.h"
#include "../../../engine/include/Sprite.h"
#include "../../../engine/include/Sound.h"
#include "../../../engine/include/State.h"

class MenuBox : public GameObject
{
  public:
    MenuBox(float x, float y, std::string spFile1, std::string spFile2, std::string type);

    void Update(float dt);
    void Render();
    void NotifyCollision(GameObject& other);

    bool IsDead();
    bool Is(std::string type);

  private:
    Sprite sp1, sp2;
    bool isMouseInside, click;
    std::string type;
    Sound thunder, clickSound;
};

#endif /* MENUBOX_H_ */
