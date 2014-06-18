/*
 * Sprite.h
 *
 *  Created on: Mar 22, 2014
 *      Author: Gabriel Naves
 *
 *  Description: Loads and renders an image
 *
 */

#ifndef SPRITE_H_
#define SPRITE_H_

#include "Resource.h"
#include "Game.h"

class Sprite
{
  public:
    Sprite();
    Sprite(const Sprite& sp);
    Sprite(std::string file, int frameCount = 1, float frameTime = 1, bool repeat = true);
    ~Sprite();

    void Open(std::string file);
    void Update(float dt, bool forward = true);
    void Render(int x, int y, float angle = 0, SDL_RendererFlip flip = SDL_FLIP_NONE);

    void SetFrame(int frame);
    void SetFrameCount(int frameCount);
    void SetFrameTime(float fameTime);
    void SetRepeat(bool repeat);
    void SetClip(int x, int y, int w, int h);
    void SetScaleX(float scale);
    void SetScaleY(float scale);

    int GetWidth();
    int GetHeight();
    int GetCurrentFrame();
    int GetFrameCount();
    float GetFrameTime();
    bool IsOpen();

  private:
    SDL_Texture* texture;
    SDL_Rect dimensions, clipRect;

    float scaleX, scaleY, timeElapsed, frameTime;
    int frameCount, currentFrame;
    bool repeat;

    // Name of the file containing the texture currently opened.
    std::string fileName;
};

#endif /* SPRITE_H_ */
