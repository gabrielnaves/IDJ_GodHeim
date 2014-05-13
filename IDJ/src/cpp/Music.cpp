/*
 * Music.cpp
 *
 *  Created on: May 4, 2014
 *      Author: Gabriel Naves
 */

#include "../include/Music.h"

std::unordered_map<std::string, Resource> Music::assetTable;

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
        assetTable.at(file).UserCount--;
}

void Music::Play(int times)
{
    Mix_PlayMusic(music, times);
}

void Music::Stop()
{
    Mix_FadeOutMusic(0);
}

void Music::Open(std::string file)
{
    if (music != NULL)
        assetTable.at(file).UserCount--;
    this->file = file;
    if (assetTable.find(file) == assetTable.end())
    {
        music = Mix_LoadMUS(file.c_str());
        if (music == NULL)
            std::cerr << "ERROR! " << SDL_GetError() << std::endl;
        Resource resource;
        resource.UserCount = 1;
        resource.data.music = music;
        assetTable.emplace(file, resource);
    }
    else
    {
        music = assetTable.at(file).data.music;
        assetTable.at(file).UserCount++;
    }
}

bool Music::IsOpen()
{
    return music != NULL ? true : false;
}

void Music::Clear()
{
    std::vector<std::string> filesToErase;
    for (auto it = assetTable.begin(); it != assetTable.end(); ++it)
        if (it->second.UserCount == 0)
        {
            Mix_FreeMusic(it->second.data.music); // If a texture is allocated, destroy it.
            filesToErase.push_back(it->first);
        }
    for (int i = 0; i < (int)filesToErase.size(); i++)
        assetTable.erase(filesToErase[i]);
}
