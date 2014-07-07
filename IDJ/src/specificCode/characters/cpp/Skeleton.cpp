/*
 * Skeleton.cpp
 *
 *  Created on: Jul 7, 2014
 *      Author: icaro
 */

#include "../include/Skeleton.h"

Skeleton::Skeleton(float x, float y)
	: restSp("img/characters/esqueletoparadosobedesce.png",4,0.25), walkSp("img/characters/esqueletoandando.png",4,0.1)
{
	box.Set(x,y,restSp.GetWidth(),restSp.GetHeight());
	rotation = 0;
    hp = 1;
    facingRight = false;
    SetState(SkeletonNamespace::RESTING);
    visionField.Set(640, (box.GetY()+box.GetH())-110, SkeletonNamespace::VISION_DISTANCE, 110);
}

void Skeleton::SetState(SkeletonNamespace::State state)
{
	this->state = state;
}

void Skeleton::Update(float dt)
{
	if (state == SkeletonNamespace::RESTING) Rest(dt);
	if (state == SkeletonNamespace::WALKING) Walk(dt);
	if (state == SkeletonNamespace::ATTACKING) Attack(dt);
}

void Skeleton::Rest(float dt)
{
	restSp.Update(dt);
	Rect target(FindClosestCharacter());
	restSp.Update(dt);
	// If the closest character is within the wolf's field of view, run towards it
	if (Collision::IsColliding(target, visionField, 0, 0))
	{
		state = SkeletonNamespace::WALKING;
	    walkSp.SetFrame(1);
	}
}

void Skeleton::Walk(float dt)
{
    Rect target(FindClosestCharacter());
    if (!Collision::IsColliding(target, visionField, 0, 0))
    {
        state = SkeletonNamespace::RESTING;
        walkSp.SetFrame(1);
        return;
    }
	walkSp.Update(dt);
    float distance = target.Center().GetX() - box.Center().GetX();
    float signal = (distance >= 0 ? 1 : -1);
    facingRight = (signal == 1 ? true : false);
    if (abs(distance) >= 60)
        box.MoveRect(dt*SkeletonNamespace::WALK_SPEED*signal, 0);
//    else state = SkeletonNamespace::ATTACKING;
}

void Skeleton::Attack(float dt)
{

}

void Skeleton::Render()
{
	if (state == SkeletonNamespace::RESTING)
		restSp.Render(box.GetX()-Camera::pos.GetX(), box.GetY()-Camera::pos.GetY(), 0, (facingRight ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL));
	if (state == SkeletonNamespace::WALKING)
		walkSp.Render(box.GetX()-Camera::pos.GetX(), box.GetY()-Camera::pos.GetY(), 0, (facingRight ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL));
}

void Skeleton::NotifyCollision(GameObject& other)
{

}

bool Skeleton::IsDead()
{
	return (hp<=0 ? true : false);
}

bool Skeleton::Is(std::string type)
{
	return (type == "Skeleton" ? true : false);
}

void Skeleton::Die()
{
    Sprite skeletonDeath("img/characters/esqueletomorre.png", 12, 0.1);
    StillAnimation *sa = new StillAnimation(box.Center().GetX(),box.Center().GetY(),rotation,skeletonDeath,1.2,true);
    Game::GetInstance().GetCurrentState().AddObject(sa);
}

Rect Skeleton::FindClosestCharacter()
{
    if (Loki::characterLoki == NULL or Thor::characterThor == NULL) return Rect();
    Rect loki = Loki::characterLoki->box;
    Rect thor = Thor::characterThor->box;
    float lokiDistance, thorDistance;
    if (Collision::IsColliding(loki, visionField, 0, 0))
        lokiDistance = loki.Center().Distance(box.Center());
    else lokiDistance = 9999999;
    if (Collision::IsColliding(thor, visionField, 0, 0))
        thorDistance = thor.Center().Distance(box.Center());
    else thorDistance = 9999999;
    if (thorDistance < lokiDistance) return thor;
    return loki;
}
