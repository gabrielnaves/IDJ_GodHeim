/*
 * Thor.h
 *
 *  Created on: May 19, 2014
 *      Author: Gabriel Naves
 *              Icaro Mota
 */

#ifndef THOR_H_
#define THOR_H_

#include "Character.h"
#include "Barrier.h"

class Thor : public Character
{
  public:
    Thor(float x, float y, MovementMap& movMap);
    ~Thor();

    void NotifyCollision(GameObject& other);
    bool Is(std::string type);
    static Thor *characterThor;

  private:
    void Input();
    void UpdateSprite();
    void UpdateVerticalState();
    void UpdatesStateOnTheFall();
    void Act();
    void Hit();
};

#endif /* THOR_H_ */
