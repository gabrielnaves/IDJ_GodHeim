/*
 * Music.h
 *
 *  Created on: May 4, 2014
 *      Author: Gabriel Naves
 */

#ifndef MUSIC_H_
#define MUSIC_H_

#include <unordered_map>
#include <string>
#include <iostream>
#include <vector>
#include "Resource.h"

class Music
{
  public:
    Music();
    Music(std::string file);
    ~Music();

    void Play(int times);
    void Stop();
    void Open(std::string file);
    bool IsOpen();

    static void Clear();

  private:
    std::string file;
    Mix_Music* music;

    static std::unordered_map<std::string, Resource> assetTable;
};

#endif /* MUSIC_H_ */
