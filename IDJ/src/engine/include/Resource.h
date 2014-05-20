/*
 * Resource.h
 *
 *  Created on: May 3, 2014
 *      Author: Gabriel Naves
 */

#ifndef RESOURCE_H_
#define RESOURCE_H_

#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

class Resource
{
  public:
    union ResourcePtr
    {
        SDL_Texture* texture;
        Mix_Music* music;
        Mix_Chunk* chunk;
        TTF_Font* font;
    };

    Resource(SDL_Texture* texture);
    Resource(Mix_Music* music);
    Resource(Mix_Chunk* chunk);
    Resource(TTF_Font* font);

    int userCount;
    ResourcePtr data;
};

#endif /* RESOURCE_H_ */
