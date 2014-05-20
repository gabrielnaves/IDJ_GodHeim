/*
 * Resource.cpp
 *
 *  Created on: May 20, 2014
 *      Author: Gabriel Naves
 */

#include "../include/Resource.h"

Resource::Resource(SDL_Texture* texture)
{
	data.texture = texture;
	userCount = 1;
}

Resource::Resource(Mix_Music* music)
{
	data.music = music;
	userCount = 1;
}

Resource::Resource(Mix_Chunk* chunk)
{
	data.chunk = chunk;
	userCount = 1;
}

Resource::Resource(TTF_Font* font)
{
	data.font = font;
	userCount = 1;
}
