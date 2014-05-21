/*
 * Resource.cpp
 *
 *  Created on: May 20, 2014
 *      Author: Gabriel Naves
 */

#include "../include/Resource.h"

std::unordered_map<std::string, Resource> Resource::assetTable;

Resource::Resource(SDL_Texture* texture)
{
	data.texture = texture;
	userCount = 1;
	type = TEXTURE;
}

Resource::Resource(Mix_Music* music)
{
	data.music = music;
	userCount = 1;
	type = MUSIC;
}

Resource::Resource(Mix_Chunk* chunk)
{
	data.chunk = chunk;
	userCount = 1;
	type = CHUNK;
}

Resource::Resource(TTF_Font* font)
{
	data.font = font;
	userCount = 1;
	type = FONT;
}

void Resource::Clear()
{
	std::vector<std::string> filesToErase;
	for (auto it = Resource::assetTable.begin(); it != Resource::assetTable.end(); ++it)
		if (it->second.userCount == 0)
		{
			filesToErase.push_back(it->first);
			switch(it->second.type)
			{
				case TEXTURE:
					SDL_DestroyTexture(it->second.data.texture); // If a texture is allocated, destroy it.
					break;
				case MUSIC:
					Mix_FreeMusic(it->second.data.music); // If a music is allocated, destroy it.
					break;
				case CHUNK:
					Mix_FreeChunk(it->second.data.chunk); // If a chunk is allocated, destroy it.
					break;
				case FONT:
					TTF_CloseFont(it->second.data.font); // If a font is allocated, destroy it.
					break;
			}
		}
	for (int i = 0; i < (int)filesToErase.size(); i++)
		Resource::assetTable.erase(filesToErase[i]);
}
