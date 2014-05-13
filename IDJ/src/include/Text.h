/*
 * Text.h
 *
 *  Created on: May 4, 2014
 *      Author: Gabriel Naves
 */

#ifndef TEXT_H_
#define TEXT_H_

#include <ostream>
#include "Music.h"
#include "Rect.h"
#include "Game.h"

enum TextStyle { TEXT_SOLID, TEXT_SHADED, TEXT_BLENDED };

class Text
{
  public:
    Text(std::string fontFile, int fontSize, TextStyle style,
         std::string text, SDL_Color color, int x = 0, int y = 0);
    ~Text();

    void Render(int cameraX = 0, int cameraY = 0);
    void SetPos(int x, int y, bool centerX = false, bool centerY = false);
    void SetText(std::string text);
    void SetColor(SDL_Color color);
    void SetStyle(TextStyle style);
    void SetFontSize(int fontSize);

    static void Clear();

  private:
    void RemakeTexture();

    TTF_Font* font;
    SDL_Texture* texture;

    std::string fontFile;
    std::string text;
    TextStyle style;
    int fontSize;
    SDL_Color color;
    Rect box;

    static std::unordered_map<std::string, Resource> assetTable;
};

#endif /* TEXT_H_ */
