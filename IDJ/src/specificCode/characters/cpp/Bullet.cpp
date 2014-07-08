/*
 * Bullet.cpp
 *
 *  Created on: May 29, 2014
 *      Author: icaro
 */

#include "../include/Bullet.h"

/**
 * @Param angle must be in radians
 */
Bullet::Bullet(float x, float y, float angle, float speed, float maxDistance, Sprite sprite, std::string shooter, MovementMap movMap)
	: sp(sprite), movementMap(movMap)
{
	box.Set(x,y,sp.GetWidth(),sp.GetHeight());
	this->speed.Set(speed*cos(angle),speed*sin(angle));
	distanceLeft = maxDistance;
	rotation = angle*360/(2*M_PI);
	this->shooter = shooter;
	saSprite = NULL;
	flip =  SDL_FLIP_NONE;
}

void Bullet::SetStillAnimation(std::string sp,int frameCount, float frameTime)
{
    saSprite = new Sprite(sp, frameCount, frameTime);
}

void Bullet::Update(float dt)
{
	timeElapsed.Update(dt);
	box.MoveRect(speed.GetX()*dt,speed.GetY()*dt);
	distanceLeft -= sqrt(pow(speed.GetX()*dt, 2) + pow(speed.GetY()*dt, 2));
	sp.Update(dt);
	CheckCollisionWithWall();
}

void Bullet::CheckCollisionWithWall()
{
    // Checks the right limit
    if (!movementMap.IsZero(box.Center().GetX() + box.GetW()/2, box.Center().GetY()))
        distanceLeft = 0;
    // Checks the left limit
    if (!movementMap.IsZero(box.Center().GetX() - box.GetW()/2, box.Center().GetY()))
    	distanceLeft = 0;
    //Checks the lower limit
    if (!movementMap.IsZero(box.Center().GetX(), box.Center().GetY() + box.GetH()/2))
    {
        distanceLeft = 0;
        if (saSprite != NULL)
        {
            StillAnimation *sa = new StillAnimation(box.Center().GetX(),box.Center().GetY(),rotation,*saSprite,0.4,true);
        	Game::GetInstance().GetCurrentState().AddObject(sa);
        }
    }
}

void Bullet::Render()
{
	sp.Render(box.GetX()-Camera::pos.GetX(),box.GetY()-Camera::pos.GetY(),rotation, flip);
}

bool Bullet::IsDead()
{
	return(distanceLeft<=0 ? true:false);
}

bool Bullet::Is(std::string type)
{
	return (type == shooter+"Bullet" ? true : false);
}

void Bullet::NotifyCollision(GameObject &other)
{
    if (shooter == "Loki")
        if (other.Is("Goat") or other.Is("Wolf") or other.Is("PlantBarrier") or other.Is("Skeleton"))
            distanceLeft = 0;
    if (shooter == "CDragon")
    {
    	if ((other.Is("Thor") or other.Is("Loki")) and distanceLeft > 10)
    		distanceLeft = 10;
    	if (other.Is("FloatingBlock") and distanceLeft > 10 and timeElapsed.Get()>3)
    	{
            distanceLeft = 10;
            if (saSprite != NULL)
            {
                StillAnimation *sa = new StillAnimation(box.Center().GetX(),box.Center().GetY(),rotation,*saSprite,0.4,true);
            	Game::GetInstance().GetCurrentState().AddObject(sa);
            }
    	}
    }
}

void Bullet::FlipImage(SDL_RendererFlip flip)
{
	this->flip = flip;
}
