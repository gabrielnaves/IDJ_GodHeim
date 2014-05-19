/*
 * Sound.cpp
 *
 *  Created on: May 4, 2014
 *      Author: Gabriel Naves
 */

#include "../include/Sound.h"

std::unordered_map<std::string, Resource> Sound::assetTable;

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
        assetTable.at(file).UserCount--;
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
        assetTable.at(file).UserCount--;
    this->file = file;
    if (assetTable.find(file) == assetTable.end())
    {
        chunk = Mix_LoadWAV(file.c_str());
        if (chunk == NULL)
            std::cerr << "ERROR! " << SDL_GetError() << std::endl;
        Resource resource;
        resource.UserCount = 1;
        resource.data.chunk = chunk;
        assetTable.emplace(file, resource);
    }
    else
    {
        chunk = assetTable.at(file).data.chunk;
        assetTable.at(file).UserCount++;
    }
}

bool Sound::IsOpen()
{
    return chunk != NULL ? true : false;
}

void Sound::Clear()
{
    std::vector<std::string> filesToErase;
    for (auto it = assetTable.begin(); it != assetTable.end(); ++it)
        if (it->second.UserCount == 0)
        {
            Mix_FreeChunk(it->second.data.chunk); // If a texture is allocated, destroy it.
            filesToErase.push_back(it->first);
        }
    for (int i = 0; i < (int)filesToErase.size(); i++)
        assetTable.erase(filesToErase[i]);
}
