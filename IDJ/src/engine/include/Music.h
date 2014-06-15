/*
 * Music.h
 *
 *  Created on: May 4, 2014
 *      Author: Gabriel Naves
 *
 *  Description: Manages the musics that will be played in the game. Only one music may be played at a time.
 *
 */

#ifndef MUSIC_H_
#define MUSIC_H_

#include <iostream>
#include "Resource.h"

class Music
{
  public:
    Music();
    Music(std::string file);
    ~Music();

    void Play(int times);
    void Stop(float fadeTime = 0);
    void Open(std::string file);
    bool IsOpen();

  private:
    std::string file;
    Mix_Music* music;
};

#endif /* MUSIC_H_ */
