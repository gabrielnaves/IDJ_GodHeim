/*
 * Character.h
 *
 *  Created on: May 23, 2014
 *      Author: Icaro Mota
 *              Gabriel Naves
 */

#ifndef CHARACTER_H_
#define CHARACTER_H_

#include "../../../Engine.h"

enum ActionState {NONE, CLIMBING};
enum VerticalState {STANDING, JUST_JUMPED, JUMPING, FALLING};
enum HorizontalState {STANDING_RIGHT, STANDING_LEFT, MOVING_RIGHT, MOVING_LEFT};

class MovementState;

class Character : public GameObject
{
  public:
    Character(MovementMap& movMap,std::string,int frameCount,float frameTime,
            std::string jump,int jumpFrameCount,float jumpFrameTime,std::string climb, int cFrameCount, float cFrameTime);
    virtual ~Character() {}
    bool IsClimbing();
    void CancelAction();
    void ReleasesStairs();
    void HoldStairs();

    bool IsDead();
    void Render();

    VerticalState GetVState();
    HorizontalState GetHState();
    void SetVState(VerticalState vS);
    void SetHState(HorizontalState hS);
    void SetActionState(ActionState actionState);

    bool canHoldStairs;
    bool insideBridge;
    bool barrierSuspended;
    Point speed;
    float dt;

    int horizontal, vertical;
    bool actionButton;
  protected:
    virtual void Input() = 0;
    virtual void UpdateSprite() = 0;
    virtual void UpdateVerticalState() = 0;
    virtual void Act() = 0;
    virtual void UpdatesStateOnTheFall() = 0;
    virtual bool IndividualUpdateSpeed();

    void Update(float dt);
    void UpdatePrevState();
    void ChangeSp(std::string spType, std::string sp, int frameCount = 1, int currentFrame = 1, bool repeat = true);
    void ChangeMovementState(std::string type);

    int hp;
    Sprite characterSp, walkSp, jumpSp, climbSp;
    MovementMap& movementMap;
    MovementState *movement;

    ActionState actionState, prevActionState;
    VerticalState vState, prevVState;
    HorizontalState hState, prevHState;

    bool shouldRender; //flag in case the characters should not be rendered for being covered by something

    const float HP = 100;
  private:
    void Move();
    void UpdateSpeed();
    void UpdateHorizontalState();
    void UpdateState();
    void CheckMovementLimits();
};

#endif /* CHARACTER_H_ */
