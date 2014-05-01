/*
 * Sprite.cpp
 *
 *  Created on: Mar 22, 2014
 *      Author: Gabriel Naves
 */

#include "../include/Sprite.h"

std::unordered_map<std::string, SDL_Texture*> Sprite::assetTable;

Sprite::Sprite()
{
    texture = NULL;
    scaleX = scaleY = 1;
    frameTime = 1;
    frameCount = 1;
    timeElapsed = 0;
    currentFrame = 1;
    repeat = true;
}

Sprite::Sprite(std::string file, int frameCount, float frameTime, bool repeat)
{
    texture = NULL;
    scaleX = scaleY = 1;
    this->frameCount = frameCount;
    this->frameTime = frameTime;
    timeElapsed = 0;
    currentFrame = 1;
    this->repeat = repeat;
    Open(file);
}

Sprite::~Sprite()
{
}

void Sprite::Open(std::string file)
{
    if (assetTable.find(file) == assetTable.end())
    {
        texture = IMG_LoadTexture(GameBase::GetInstance().GetRenderer(), file.c_str());
        if (texture == NULL)
            std::cerr << "ERROR! " << SDL_GetError() << std::endl;
        else
            assetTable.emplace(file, texture);
    }
    else
        texture = assetTable.at(file);

    SDL_QueryTexture(texture, 0, 0, &dimensions.w, &dimensions.h);
    SetClip(0, 0 , dimensions.w/frameCount, dimensions.h);
}

void Sprite::SetClip(int x, int y, int w, int h)
{
    clipRect.x = x;
    clipRect.y = y;
    clipRect.w = w;
    clipRect.h = h;
}

void Sprite::Update(float dt)
{
    timeElapsed += dt;
    if (timeElapsed >= frameTime)
    {
        currentFrame++;
        if (currentFrame > frameCount && repeat)
            currentFrame = 1;
        else if (currentFrame > frameCount)
            currentFrame = frameCount;
        SetClip(dimensions.w/frameCount*(currentFrame-1), 0, dimensions.w/frameCount, dimensions.h);
        timeElapsed = 0;
    }
}

void Sprite::Render(int x, int y, float angle)
{
    SDL_Rect dstrect = dimensions;
    dstrect.x = x;
    dstrect.y = y;
    dstrect.w = clipRect.w * scaleX;
    dstrect.h = clipRect.h * scaleY;

    SDL_RenderCopyEx(GameBase::GetInstance().GetRenderer(), texture, &clipRect,
                     &dstrect, angle, NULL, SDL_FLIP_NONE);
}

void Sprite::Clear()
{
    for (auto it = assetTable.begin(); it != assetTable.end(); ++it)
        if (it->second != NULL)
            SDL_DestroyTexture(it->second); // If a texture is allocated, destroy it.
    assetTable.clear();
}

bool Sprite::IsOpen() { return (texture != NULL ? true : false); }

// Get Methods //
int Sprite::GetWidth() { return (dimensions.w/frameCount * scaleX); }
int Sprite::GetHeight() { return (dimensions.h * scaleY); }

// Set Methods //
void Sprite::SetScaleX(float scale) { scaleX = scale; }
void Sprite::SetScaleY(float scale) { scaleY = scale; }
void Sprite::SetFrameCount(int frameCount) { this->frameCount = frameCount; }
void Sprite::SetFrameTime(float frameTime) { this->frameTime = frameTime; }

void Sprite::SetFrame(int frame)
{
    if (frame <= 0 || frame > frameCount)
    {
        std::cerr << "ERROR! Invalid frame value." << std::endl;
        return;
    }
    currentFrame = frame;
    SetClip((dimensions.w/frameCount)*(currentFrame-1), 0, dimensions.w/frameCount, dimensions.h);
}
