/*
 * Timer.h
 *
 *  Created on: May 2, 2014
 *      Author: Gabriel Naves
 *
 *  Description: A time counter;
 *
 */

#ifndef TIMER_H_
#define TIMER_H_

class Timer
{
  public:
    Timer();
    void Update(float dt);
    void Restart();
    float Get();

  private:
    float time;
};

#endif /* TIMER_H_ */
