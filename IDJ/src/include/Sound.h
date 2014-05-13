/*
 * Sound.h
 *
 *  Created on: May 4, 2014
 *      Author: Gabriel Naves
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

    static void Clear();

  private:
    std::string file;
    Mix_Chunk* chunk;
    int channel;

    static std::unordered_map<std::string, Resource> assetTable;
};

#endif /* SOUND_H_ */
