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

    void Update(float dt);
    void Render();
    void NotifyCollision(GameObject& other);
    bool Is(std::string type);
    bool IsClimbing();
    static Thor *characterThor;

  private:
    enum ActionState {NONE, CLIMBING};
    ActionState actionState;

    void Input();
    void Move(float dt);
    void UpdateSprite();
    void UpdateVerticalState();
    void UpdatesStateOnTheFall();
    void Act();
};

#endif /* THOR_H_ */
