/*
 * Sound.cpp
 *
 *  Created on: May 4, 2014
 *      Author: Gabriel Naves
 */

#include "../include/Sound.h"

Sound::Sound()
{
    chunk = NULL;
    channel = -1;
}

Sound::Sound(std::string file)
{
    chunk = NULL;
    Open(file);
}

Sound::~Sound()
{
    if (chunk != NULL)
        Resource::assetTable.at(file).userCount--;
}

void Sound::Play(int times)
{
    channel = Mix_PlayChannel(-1, chunk, times);
}

void Sound::Stop()
{
    Mix_HaltChannel(channel);
}

void Sound::Open(std::string file)
{
    if (chunk != NULL)
        Resource::assetTable.at(this->file).userCount--;
    this->file = file;
    //if the music does not exist in the table of assets, loads it now
    if (Resource::assetTable.find(file) == Resource::assetTable.end())
    {
        chunk = Mix_LoadWAV(file.c_str());
        //checks for eventual errors
        if (chunk == NULL)
            std::cerr << "ERROR! " << SDL_GetError() << std::endl;
        Resource resource(chunk);
        Resource::assetTable.emplace(file, resource); //puts the new resource in the hash map
    }
    else
    {
        chunk = Resource::assetTable.at(file).data.chunk; //if the sound already exists, copies it into chunk
        Resource::assetTable.at(file).userCount++; //adds to the count of users of that sound
    }
}

bool Sound::IsOpen()
{
    return chunk != NULL ? true : false;
}
