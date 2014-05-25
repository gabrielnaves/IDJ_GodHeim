/*
 * Barrier.cpp
 *
 *  Created on: May 22, 2014
 *      Author: icaro
 */

#include "../include/Barrier.h"

Barrier* Barrier::barrier;

Barrier::Barrier()
{
	box.Set(GetCorner(),DIAMETER,DIAMETER);
	rotation = 0;
	barrier = this;
}

Barrier::~Barrier()
{
	barrier = NULL;
}

/**
 * Sets the point in box based on the coordinate of the center of the barrier
 */
Point Barrier::GetCorner()
{
	return (Point(FindCenter().GetX() - DIAMETER/2, FindCenter().GetY() - DIAMETER/2));
}

/**
 * Find the center of the barrier, which is located in the middle of the 2 characters
 */
Point Barrier::FindCenter()
{
	Point thor = Thor::characterThor->box.Center();
	Point loki = Loki::characterLoki->box.Center();
	Point center;

	float Y, y; //Y > y
	float X, x; //X > x

	//sees where is the greater Y value
	if (thor.GetY() > loki.GetY())
		Y = thor.GetY(), y = loki.GetY();
	else
		Y = loki.GetY(), y = thor.GetY();
	//sees where is the greater X value
	if (thor.GetX() > loki.GetX())
		X = thor.GetX(), x = loki.GetX();
	else
		X = loki.GetX(), x = thor.GetX();

	center.Set((X-x)/2 + x,(Y-y)/2 + y);
	return(center);
}

void Barrier::Update(float dt)
{
	box.SetPoint(GetCorner());
}

void Barrier::Render() {}
/**
 * Should not have to colide with anything
 */
void Barrier::NotifyCollision(GameObject& other){}

bool Barrier::IsDead()
{
	return (Thor::characterThor == NULL or Loki::characterLoki == NULL);
}
bool Barrier::Is(std::string type)
{
	return type == "Barrier" ? true : false;
}
