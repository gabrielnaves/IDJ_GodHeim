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
        Resource::assetTable.at(file).userCount--;
    this->file = file;
    if (Resource::assetTable.find(file) == Resource::assetTable.end())
    {
        chunk = Mix_LoadWAV(file.c_str());
        if (chunk == NULL)
            std::cerr << "ERROR! " << SDL_GetError() << std::endl;
        Resource resource(chunk);
        Resource::assetTable.emplace(file, resource);
    }
    else
    {
        chunk = Resource::assetTable.at(file).data.chunk;
        Resource::assetTable.at(file).userCount++;
    }
}

bool Sound::IsOpen()
{
    return chunk != NULL ? true : false;
}
