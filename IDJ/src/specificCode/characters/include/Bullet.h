/*
 * Bullet.h
 *
 *  Created on: May 29, 2014
 *      Author: icaro
 *
 * 	Description: An object that collides with characters.
 */

#ifndef BULLET_H_
#define BULLET_H_

#include "../../../Engine.h"
#include "Goat.h"

class Bullet : public GameObject {
  public:
	Bullet(float x, float y, float angle, float speed, float maxDistance, Sprite sprite, std::string shooter, MovementMap movMap);
	bool IsDead();
	void Render();
	void Update(float dt);
	void NotifyCollision(GameObject &other);
	bool Is(std::string type);
  private:
	void CheckCollisionWithWall();
	Sprite sp;
	Point speed;
	float distanceLeft;
	std::string shooter;
    MovementMap movementMap;
};

#endif /* BULLET_H_ */
