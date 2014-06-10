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

class MenuBox : public GameObject
{
  public:
    MenuBox(float x, float y, Sprite sprite1, Sprite sprite2);
    ~MenuBox();

    void Update(float dt);
    void Render();
    void NotifyCollision(GameObject& other);

    bool IsDead();
    bool Is(std::string type);

  private:
    Sprite sp1, sp2;
    bool isMouseInside;
};

#endif /* MENUBOX_H_ */
