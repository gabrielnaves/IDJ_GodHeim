/*
 * Item.h
 *
 *  Created on: Jun 15, 2014
 *      Author: icaro
 */

#ifndef ITEM_H_
#define ITEM_H_

#include "../../../engine/include/GameObject.h"
#include "../../../engine/include/Sprite.h"
#include "../../../engine/include/Camera.h"

class Item : public GameObject
{
  public:
    Item(int x, int y, std::string imageAdress, std::string name);
    virtual ~Item();
    void Update(float dt);
    void Render();
    bool HasItem();
    bool Is(std::string type);
    bool IsCalled(std::string name);

  private:
    Sprite itemSp;
    std::string name;
    bool hasItem;
};

#endif /* ITEM_H_ */
