/*
 * Sprite.cpp
 *
 *  Created on: Mar 22, 2014
 *      Author: Gabriel Naves
 */

#include "../include/Sprite.h"

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

/**
 * Copy constructor. Copies all data from the sprite given as parameter
 * and increases the user count for the texture being used.
 */
Sprite::Sprite(const Sprite& sp)
{
    texture = sp.texture;
    dimensions = sp.dimensions;
    clipRect = sp.clipRect;
    scaleX = sp.scaleX;
    scaleY = sp.scaleY;
    frameCount = sp.frameCount;
    frameTime = sp.frameTime;
    timeElapsed = sp.timeElapsed;
    currentFrame = sp.currentFrame;
    repeat = sp.repeat;
    fileName = sp.fileName;
    Resource::assetTable.at(fileName).userCount++;
}

Sprite::Sprite(std::string file, int frameCount, float frameTime, bool repeat)
{
    scaleX = scaleY = 1;
    texture = NULL;
    timeElapsed = 0;
    currentFrame = 1;
    this->frameCount = frameCount;
    this->frameTime = frameTime;
    this->repeat = repeat;
    Open(file);
}

Sprite::~Sprite()
{
    if (texture != NULL)
    	Resource::assetTable.at(fileName).userCount--;
}

void Sprite::Open(std::string file)
{
    if (texture != NULL)
    	Resource::assetTable.at(fileName).userCount--;
    fileName = file;
    //if the image does not exist in the table of assets, sets the texture to the one of the given image
    if (Resource::assetTable.find(file) == Resource::assetTable.end())
    {
        texture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), file.c_str());
        //checks for eventual errors
        if (texture == NULL)
            std::cerr << "ERROR! " << SDL_GetError() << std::endl;
        Resource resource(texture);
        Resource::assetTable.emplace(file, resource); //puts the new texture in the hash map
    }
    else
    {
        texture = Resource::assetTable.at(file).data.texture; //if the image already exists, copies it into texture
        Resource::assetTable.at(file).userCount++; //adds to the count of users of that image
    }

    //this sets the widght and height of the picture into dimensions
    SDL_QueryTexture(texture, 0, 0, &dimensions.w, &dimensions.h);
    SetClip(0, 0 , dimensions.w/frameCount, dimensions.h);
}

void Sprite::SetClip(int x, int y, int w, int h)
{
    clipRect.x = x; clipRect.y = y; clipRect.w = w; clipRect.h = h;
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

void Sprite::Render(int x, int y, float angle, SDL_RendererFlip flip)
{
	/*Angle is given in degrees*/
    SDL_Rect dstrect = dimensions;
    dstrect.x = x;
    dstrect.y = y;
    dstrect.w = clipRect.w * scaleX;
    dstrect.h = clipRect.h * scaleY;

    SDL_RenderCopyEx(Game::GetInstance().GetRenderer(), texture, &clipRect,
                     &dstrect, angle, NULL, flip);
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

int Sprite::GetCurrentFrame()
{
    return (currentFrame);
}

int Sprite::GetFrameCount()
{
    return (frameCount);
}
float Sprite::GetFrameTime()
{
    return (frameTime);
}
