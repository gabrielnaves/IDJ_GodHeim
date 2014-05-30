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
    Character(MovementMap movMap);
    virtual ~Character() {}
    virtual void Update(float dt) = 0;
    virtual void Render() = 0;
    virtual bool Is(std::string type) = 0;

    virtual void NotifyCollision(GameObject& other) = 0;
    bool IsDead();
    Point GetSpeed();

  protected:
    void UpdateSpeed(float dt);
    void UpdateHorizontalState();
    void UpdateState();
    virtual void Move(float dt) = 0;
    void CheckMovementLimits();
    virtual void UpdateSprite() = 0;
    virtual void UpdateVerticalState() = 0;
    virtual void Action() = 0;

    enum VerticalState { STANDING, JUST_JUMPED, JUMPING, FALLING };
    enum HorizontalState { STANDING_RIGHT, STANDING_LEFT, MOVING_RIGHT, MOVING_LEFT};

    VerticalState vState;
    HorizontalState hState;
    int hp;
    Sprite tempCharacterSp;
    MovementMap movementMap;
    Point speed;

    int horizontal;
    bool actionButton;

    const float VEL = 200;
    const float JUMP_SPEED = -400;
    const float GRAVITY = 1000;
    const float MAX_FALLING_SPEED = 600;
};

#endif /* CHARACTER_H_ */
