/*
 * Character.h
 *
 *  Created on: May 23, 2014
 *      Author: Icaro Mota
 *              Gabriel Naves
 */

#ifndef CHARACTER_H_
#define CHARACTER_H_

#include "../../../engine/include/InputManager.h"
#include "../../../engine/include/GameObject.h"
#include "../../../engine/include/Sprite.h"
#include "../../../engine/include/Camera.h"
#include "../../../engine/include/MovementMap.h"
#include <cmath>

class Character : public GameObject
{
  public:
    Character(MovementMap& movMap);
    virtual ~Character() {}
    virtual void Update(float dt) = 0;
    virtual void Render() = 0;
    virtual bool Is(std::string type) = 0;
    virtual void NotifyCollision(GameObject& other) = 0;

    bool canHoldStairs;
    bool IsDead();
    Point GetSpeed();

  protected:
    virtual void Move(float dt) = 0;
    virtual void UpdateSprite() = 0;
    virtual void UpdateVerticalState() = 0;
    virtual void Act() = 0;
    virtual void UpdatesStateOnTheFall() = 0;

    void Climb(float dt);
    void UpdateSpeed(float dt);
    void UpdateHorizontalState();
    void UpdateState();
    void CheckMovementLimits();

    enum VerticalState {STANDING, JUST_JUMPED, JUMPING, FALLING};
    enum HorizontalState {STANDING_RIGHT, STANDING_LEFT, MOVING_RIGHT, MOVING_LEFT};

    VerticalState vState;
    HorizontalState hState;
    int hp;
    Sprite tempCharacterSp;
    MovementMap& movementMap;
    Point speed;

    int horizontal;
    int vertical;
    bool actionButton;

    const float VEL = 200;
    const float JUMP_SPEED = -500;
    const float GRAVITY = 1000;
    const float MAX_FALLING_SPEED = 600;
    const float CLIMBING_SPEED = -200;
};

#endif /* CHARACTER_H_ */
