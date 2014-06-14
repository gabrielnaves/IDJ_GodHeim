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

enum ActionState {NONE, CLIMBING};
enum VerticalState {STANDING, JUST_JUMPED, JUMPING, FALLING};
enum HorizontalState {STANDING_RIGHT, STANDING_LEFT, MOVING_RIGHT, MOVING_LEFT};

class Character : public GameObject
{
  public:
    Character(MovementMap& movMap,std::string,int frameCount,float frameTime,std::string jump,int jumpFrameCount,float jumpFrameTime);
    virtual ~Character() {}
    bool IsClimbing();
    void CancelAction();
    virtual void ReleasesStairs() = 0;
    virtual void HoldStairs() = 0;

    bool canHoldStairs;
    bool IsDead();
    void Render();
    Point GetSpeed();

    VerticalState GetVState();
    HorizontalState GetHState();
    void SetVState(VerticalState vS);
    void SetHState(HorizontalState hS);

    bool insideBridge;

  protected:
    virtual void Move(float dt) = 0;
    virtual void UpdateSprite(float dt) = 0;
    virtual void UpdateVerticalState() = 0;
    virtual void Act() = 0;
    virtual void UpdatesStateOnTheFall() = 0;

    void Climb(float dt);
    void UpdateSpeed(float dt);
    void UpdateHorizontalState();
    void UpdateState();
    void CheckMovementLimits();
    void UpdatePrevState();

    int hp;
    Sprite characterSp;
    Sprite walkSp;
    Sprite jumpSp;
    MovementMap& movementMap;
    Point speed;

    ActionState actionState;
    VerticalState vState;
    HorizontalState hState;
    VerticalState prevVState;
    HorizontalState prevHState;

    int horizontal;
    int vertical;
    bool actionButton;

    const float HP = 100;
    const float VEL = 200;
    const float JUMP_SPEED = -500;
    const float GRAVITY = 1000;
    const float MAX_FALLING_SPEED = 600;
    const float CLIMBING_SPEED = -200;
};

#endif /* CHARACTER_H_ */
