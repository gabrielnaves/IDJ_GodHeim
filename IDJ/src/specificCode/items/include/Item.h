/*
 * Item.h
 *
 *  Created on: Jun 15, 2014
 *      Author: icaro
 */

#ifndef ITEM_H_
#define ITEM_H_

#include "../../../Engine.h"
#include "ItemFlags.h"

class Item : public GameObject
{
  public:
    Item(int x, int y, std::string imageAdress, std::string name);
    Item(int x, int y, std::string imageAdress, std::string name, bool thorCatches, bool lokiCatches);
    Item(int x, int y, std::string imageAdress, std::string name, bool thorCatches, bool lokiCatches, bool delayed, float delay);
    virtual ~Item();
    void Update(float dt);
    void Render();
    void NotifyCollision(GameObject& other);
    bool Is(std::string type);
    bool IsDead();

  private:
    void Hover(float dt);
    void SetConstructor(int x, int y, std::string imageAdress, std::string name, bool thorCatches, bool lokiCatches, bool delayed, float delay);

    Sprite itemSp;
    std::string name;
    Timer delay;
    bool hasItem, disappear, delayed;
    bool thorCatches, lokiCatches;
    float delayTime, angle, initialY;
};

#endif /* ITEM_H_ */
