/*
 * Character.h
 *
 *  Created on: May 23, 2014
 *      Author: Icaro Mota
 *              Gabriel Naves
 */

#ifndef CHARACTER_H_
#define CHARACTER_H_

#include <vector>
#include "../../../Engine.h"
#include "../../items/include/ItemFlags.h"
#include "HpBar.h"

enum ActionState {NONE, CLIMBING};
enum VerticalState {STANDING, JUST_JUMPED, JUMPING, FALLING};
enum HorizontalState {STANDING_RIGHT, STANDING_LEFT, MOVING_RIGHT, MOVING_LEFT};

class MovementState;

class Character : public GameObject
{
  public:
    Character(MovementMap movMap,std::string,int frameCount,float frameTime,
            std::string jump,int jumpFrameCount,float jumpFrameTime,std::string climb, int cFrameCount, float cFrameTime);
    virtual ~Character() {}
    bool IsClimbing();
    void CancelAction();
    void ReleasesStairs();
    void HoldStairs();

    void Update(float dt);
    bool IsDead();
    void Render();
    void NotifyCollision(GameObject& other);
    void RenderHP();

    VerticalState GetVState();
    HorizontalState GetHState();
    void SetVState(VerticalState vS);
    void SetHState(HorizontalState hS);
    void SetActionState(ActionState actionState);

    void DealDamage();
    void Heal();
    std::string GetMovementType();

    bool canPressSwitch,pressSwitch, aboveStairs, insideBridge, barrierSuspended, actionButton;
    Point speed;
    float dt;
    int horizontal, vertical;

    ActionState actionState, prevActionState;
    VerticalState vState, prevVState;
    HorizontalState hState, prevHState;
  protected:
    virtual void UpdateSprite() = 0;
    virtual void UpdateVerticalState() = 0;
    virtual void Act() = 0;
    virtual void UpdatesStateOnTheFall() = 0;
    virtual bool IndividualMovStateSelection() = 0;

    void ChangeSp(std::string spType, std::string sp, int frameCount = 1, int currentFrame = 1, bool repeat = true);
    void ChangeMovementState(std::string type);

    std::vector<std::unique_ptr<HpBar>> hp;
    Sprite characterSp, walkSp, jumpSp, climbSp;
    MovementMap movementMap;
    MovementState *movement;

    bool shouldRender; //flag in case the characters should not be rendered for being covered by something

  private:
    void Input();
    void SelectMovState();
    void UpdateHorizontalState();
    void UpdateState();
    void CheckMovementLimits();
    void UpdatePrevState();
};

#endif /* CHARACTER_H_ */
