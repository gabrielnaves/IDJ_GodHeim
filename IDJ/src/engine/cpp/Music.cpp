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
        Resource::assetTable.at(file).userCount--;
    this->file = file;
    if (Resource::assetTable.find(file) == Resource::assetTable.end())
    {
        music = Mix_LoadMUS(file.c_str());
        if (music == NULL)
            std::cerr << "ERROR! " << SDL_GetError() << std::endl;
        Resource resource(music);
        Resource::assetTable.emplace(file, resource);
    }
    else
    {
        music = Resource::assetTable.at(file).data.music;
        Resource::assetTable.at(file).userCount++;
    }
}

bool Music::IsOpen()
{
    return music != NULL ? true : false;
}
