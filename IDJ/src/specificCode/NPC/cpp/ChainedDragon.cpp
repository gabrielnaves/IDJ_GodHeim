/*
 * ChainedDragon.cpp
 *
 *  Created on: Jul 7, 2014
 *      Author: Gabriel Naves
 */

#include "../include/ChainedDragon.h"

ChainedDragon::ChainedDragon(float x, float y, bool facingRight, MovementMap movMap) :
                            attackSp("img/characters/dragon.png", 13, 0.1, true),
                            restSp("img/characters/dragonResting.png", 2, 0.7, true),
                            movementMap(movMap)
{
	REST_TIME = (rand() % 500 + 300);
	REST_TIME = REST_TIME/100;
	box.Set(x, y, attackSp.GetWidth(), attackSp.GetHeight());
    this->facingRight = facingRight;
    rotation = 0;
    state = CDragon::RESTING;
    block = NULL;
    if (facingRight)
    	visionField.Set(box.GetX(), (box.GetY()+box.GetH())-220, CDragon::VISION_DISTANCE, CDragon::VISION_DISTANCE);
    else
    	visionField.Set(0, (box.GetY()+box.GetH())-220, box.GetX(), CDragon::VISION_DISTANCE);
    hasShot = false;
}

ChainedDragon::ChainedDragon(FloatingBlock* block, bool facingRight, MovementMap movMap) :
                            attackSp("img/characters/dragon.png", 13, 0.1, true),
                            restSp("img/characters/dragonResting.png", 2, 0.7, true),
                            movementMap(movMap)
{
	REST_TIME = (rand() % 400);
	REST_TIME = REST_TIME/100;
	float x, y;
    x = block->box.Center().GetX()-restSp.GetWidth()/2;
    y = block->box.GetY() - restSp.GetHeight() + 10;
    box.Set(x, y, restSp.GetWidth(), restSp.GetHeight());
    this->facingRight = facingRight;
    rotation = 0;
    state = CDragon::RESTING;
    this->block = block;
    if (facingRight)
    	visionField.Set(box.GetX(), (box.GetY()+box.GetH())-220, CDragon::VISION_DISTANCE, CDragon::VISION_DISTANCE);
    else
    	visionField.Set(0, (box.GetY()+box.GetH())-220, box.GetX(), CDragon::VISION_DISTANCE);
    hasShot = false;
}

void ChainedDragon::Update(float dt)
{
	UpdateVisionField();
    if (block != NULL) FollowBlock();
    if (state == CDragon::RESTING) Rest(dt);
    else if (state == CDragon::ATTACKING) Attack(dt);
}

void ChainedDragon::UpdateVisionField()
{
    if (facingRight)
    	visionField.Set(box.GetX(), (box.GetY()+box.GetH())-220, CDragon::VISION_DISTANCE, CDragon::VISION_DISTANCE);
    else
    	visionField.Set(0, (box.GetY()+box.GetH())-220, box.GetX(), CDragon::VISION_DISTANCE);
}

void ChainedDragon::FollowBlock()
{
    float x, y;
    x = block->box.Center().GetX()-box.GetW()/2;
    y = block->box.GetY() - box.GetH() + 10;
    box.Set(x, y, box.GetW(), box.GetH());
}

void ChainedDragon::Rest(float dt)
{
	Rect thor = Thor::characterThor->box;
	Rect loki = Loki::characterLoki->box;

    restSp.Update(dt);
    restTimer.Update(dt);
    if (restTimer.Get() >= REST_TIME)
    {
        // If any character is within the dragon's field of view, attacks
        if (Collision::IsColliding(thor, visionField, 0, 0) or Collision::IsColliding(loki, visionField, 0, 0))
        {
            state = CDragon::ATTACKING;
            restTimer.Restart();
            restSp.SetFrame(1);
        }
    }
}

void ChainedDragon::Attack(float dt)
{
    attackSp.Update(dt);
    attackTimer.Update(dt);
    if (attackSp.GetCurrentFrame() == 8 and !hasShot)
    	Shoot();
    if (attackTimer.Get() >= CDragon::ATTACK_TIME)
    {
        state = CDragon::RESTING;
        attackTimer.Restart();
        attackSp.SetFrame(1);
        hasShot = false;
    }
}

void ChainedDragon::Shoot()
{
	hasShot = true;
    Sprite spBullet("img/characters/dragonFirebreath.png",3,0.1);

    float shootingAngle = rand() % 20 + 35;
    if (!facingRight) shootingAngle = 180 - shootingAngle;
    shootingAngle = (shootingAngle*M_PI)/180;


//    float shootingAngle = facingRight ? M_PI/4 : 3*M_PI/4;
    Point mouth;
    if (facingRight)
    	mouth.Set(box.Center().GetX()+box.GetW()/6,box.Center().GetY()-box.GetH()/7);
    else
    	mouth.Set(box.Center().GetX()-box.GetW()/1.5,box.Center().GetY()-box.GetH()/7);
    Bullet* fireBall=new Bullet(mouth.GetX(),mouth.GetY(),shootingAngle,
    		CDragon::FIREBALL_SPEED,100000,spBullet,"CDragon",movementMap);

    fireBall->FlipImage(SDL_FLIP_HORIZONTAL);
    fireBall->SetStillAnimation("img/characters/fireStillAnimation.png", 2, 0.2);

    Game::GetInstance().GetCurrentState().AddObject(fireBall); //add the bullet to the objectArray
}

void ChainedDragon::Render()
{
    SDL_RendererFlip flip;
    flip = (facingRight ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
    switch (state)
    {
        case CDragon::RESTING:
            restSp.Render(box.GetX()-Camera::pos.GetX(), box.GetY()-Camera::pos.GetY(), rotation, flip);
            break;
        case CDragon::ATTACKING:
            attackSp.Render(box.GetX()-Camera::pos.GetX(), box.GetY()-Camera::pos.GetY(), rotation, flip);
    }
}

void ChainedDragon::NotifyCollision(GameObject& other)
{

}

bool ChainedDragon::IsDead()
{
    return false;
}

bool ChainedDragon::Is(std::string type)
{
    return type == "ChainedDragon" ? true : false;
}
