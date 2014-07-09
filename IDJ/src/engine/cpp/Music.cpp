/*
 * Music.cpp
 *
 *  Created on: May 4, 2014
 *      Author: Gabriel Naves
 */

#include "../include/Music.h"

Music::Music()
{
    music = NULL;
}

Music::Music(std::string file)
{
    music = NULL;
    Open(file);
}

Music::~Music()
{
    if (music != NULL)
        Resource::assetTable.at(file).userCount--;
}

/**
 * If times = -1, it will play indefinitely, until it is
 * stopped or changed.
 */
void Music::Play(int times)
{
    Mix_PlayMusic(music, times);
}

/**
 * Stops the music being played with a fade out effect.
 * The fading time is given in seconds.
 */
void Music::Stop(float fadeTime)
{
    fadeTime = fadeTime * 1000;
    Mix_FadeOutMusic((int)fadeTime);
}

void Music::Open(std::string file)
{
    if (music != NULL)
        Resource::assetTable.at(file).userCount--;
    this->file = file;
    //if the music does not exist in the table of assets, loads it now
    if (Resource::assetTable.find(file) == Resource::assetTable.end())
    {
        music = Mix_LoadMUS(file.c_str());
        //checks for eventual errors
        if (music == NULL)
            std::cerr << "ERROR! " << SDL_GetError() << std::endl;
        Resource resource(music);
        Resource::assetTable.emplace(file, resource); //puts the new resource in the hash map
    }
    else
    {
        music = Resource::assetTable.at(file).data.music; //if the music already exists, copies it into music
        Resource::assetTable.at(file).userCount++; //adds to the count of users of that music
    }
}

bool Music::IsOpen()
{
    return music != NULL ? true : false;
}
