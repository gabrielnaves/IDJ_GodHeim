/*
 * Bridge.cpp
 *
 *  Created on: Jun 9, 2014
 *      Author: Gabriel Naves
 */

#include "../include/Bridge.h"

Bridge::Bridge()
{
    // TODO Auto-generated constructor stub

}

Bridge::~Bridge()
{
    // TODO Auto-generated destructor stub
}

void Bridge::Update(float dt)
{

}

void Bridge::Render()
{

}

void Bridge::NotifyCollision(GameObject& other)
{

}

bool Bridge::IsDead()
{
    return false;
}

bool Bridge::Is(std::string type)
{
    return type == "Bridge" ? true : false;
}
