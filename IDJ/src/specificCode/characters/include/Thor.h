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
    Thor(float x, float y, MovementMap movMap);
    ~Thor();

    bool Is(std::string type);
    static Thor *characterThor;

    bool canHoldWolf;
  private:
    Timer hitting;
    bool IndividualMovStateSelection();
    void UpdateSprite();
    void UpdateVerticalState();
    void UpdatesStateOnTheFall();
    void Act();
    void Hit();

    const float HITTING_COOLDOWN = 0.3;
};

#endif /* THOR_H_ */
