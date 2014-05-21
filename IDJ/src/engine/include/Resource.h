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
#include <unordered_map>
#include <vector>
#include <string>

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

    static void Clear();

    int userCount;
    ResourcePtr data;

    static std::unordered_map<std::string, Resource> assetTable;

  private:
    enum dataType { TEXTURE, MUSIC, CHUNK, FONT };
    dataType type;
};

#endif /* RESOURCE_H_ */
