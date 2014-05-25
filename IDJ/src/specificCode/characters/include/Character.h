/*
 * Character.h
 *
 *  Created on: May 23, 2014
 *      Author: icaro
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

  protected:
    void UpdateSpeed(float dt);
    void UpdateHorizontalState(int horizontal);
    virtual void Move(float dt) = 0;
    void Walk(float dt);
    void Jump(float dt);
    void CheckMovementLimits();

    enum VerticalState { STANDING, JUMPING, FALLING };
    enum HorizontalState { STANDING_RIGHT, STANDING_LEFT, MOVING_RIGHT, MOVING_LEFT};
    VerticalState vState;
    HorizontalState hState;
    int hp;
    Sprite tempCharacterSp;
    MovementMap movementMap;
    Point speed;

    const float VEL = 200;
    const float JUMP_SPEED = -400;
    const float GRAVITY = 1000;
    const float MAX_FALLING_SPEED = 400;
};

#endif /* CHARACTER_H_ */
