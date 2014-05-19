/*
 * Sprite.h
 *
 *  Created on: Mar 22, 2014
 *      Author: Gabriel Naves
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
    void Update(float dt);
    void Render(int x, int y, float angle = 0);

    void SetFrame(int frame);
    void SetFrameCount(int frameCount);
    void SetFrameTime(float fameTime);
    void SetClip(int x, int y, int w, int h);
    void SetScaleX(float scale);
    void SetScaleY(float scale);

    int GetWidth();
    int GetHeight();
    bool IsOpen();

    static void Clear();

  private:
    SDL_Texture* texture;
    SDL_Rect dimensions, clipRect;

    float scaleX, scaleY, timeElapsed, frameTime;
    int frameCount, currentFrame;
    bool repeat;

    // Name of the file containing the texture currently opened.
    std::string fileName;

    static std::unordered_map<std::string, Resource> assetTable;
};

#endif /* SPRITE_H_ */
