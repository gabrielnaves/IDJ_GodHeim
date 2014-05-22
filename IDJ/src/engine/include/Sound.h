/*
 * Sound.h
 *
 *  Created on: May 4, 2014
 *      Author: Gabriel Naves
 *
 *  Description: Manages the sounds of the game.
 *
 */

#ifndef SOUND_H_
#define SOUND_H_

#include "Music.h"

class Sound
{
  public:
    Sound();
    Sound(std::string file);
    ~Sound();

    void Play(int times);
    void Stop();
    void Open(std::string file);
    bool IsOpen();

  private:
    std::string file;
    Mix_Chunk* chunk;
    int channel;
};

#endif /* SOUND_H_ */
