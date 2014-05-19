/*
 * Timer.cpp
 *
 *  Created on: May 2, 2014
 *      Author: Gabriel Naves
 */

#include "../include/Timer.h"

Timer::Timer()
{
    time = 0;
}

void Timer::Update(float dt)
{
    time = time + dt;
}

void Timer::Restart()
{
    time = 0;
}

float Timer::Get()
{
    return time;
}
