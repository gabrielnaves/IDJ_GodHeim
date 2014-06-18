/*
 * Item.h
 *
 *  Created on: Jun 15, 2014
 *      Author: icaro
 */

#ifndef ITEM_H_
#define ITEM_H_

#include "../../../Engine.h"

class Item : public GameObject
{
  public:
    Item(int x, int y, std::string imageAdress, std::string name, bool delayed = false, float delay = 0);
    virtual ~Item();
    void Update(float dt);
    void Render();
    void NotifyCollision(GameObject& other);
    bool Is(std::string type);
    bool IsDead();
    bool HasItem();

  private:
    void Hover(float dt);

    Sprite itemSp;
    std::string name;
    Timer delay;
    bool hasItem, disappear, delayed;
    float delayTime, angle, initialY;
};

#endif /* ITEM_H_ */
