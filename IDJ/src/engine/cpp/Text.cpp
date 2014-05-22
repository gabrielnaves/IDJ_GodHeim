/*
 * Text.cpp
 *
 *  Created on: May 4, 2014
 *      Author: Gabriel Naves
 */

#include "../include/Text.h"

Text::Text(std::string fontFile, int fontSize, TextStyle style,
           std::string text, SDL_Color color, int x, int y)
{
    this->fontFile = fontFile;
    this->fontSize = fontSize;
    this->style = style;
    this->text = text;
    this->color = color;
    this->box.SetPoint(Point(x, y));
    texture = NULL;
    font = NULL;

    EmplaceFont();
    if (font != NULL)
        RemakeTexture();
}

Text::~Text()
{
    Resource::assetTable.at(fontFile+std::to_string(fontSize)).userCount--;
    if (texture != NULL)
        SDL_DestroyTexture(texture);
}

void Text::Render(int cameraX, int cameraY)
{
    SDL_Rect clipRect, dstrect;
    dstrect.x = box.GetX() - cameraX, clipRect.x = 0;
    dstrect.y = box.GetY() - cameraY, clipRect.x = 0;
    dstrect.w = clipRect.w = box.GetW();
    dstrect.h = clipRect.h = box.GetH();
    SDL_RenderCopy(Game::GetInstance().GetRenderer(), texture, &clipRect, &dstrect);
}

void Text::SetPos(int x, int y, bool centerX, bool centerY)
{
    if (centerX)
        x = x - box.GetW()/2;
    if(centerY)
        y = y - box.GetH()/2;
    box.SetPoint(Point(x, y));
}

void Text::SetText(std::string text)
{
    this->text = text;
    RemakeTexture();
}

void Text::SetColor(SDL_Color color)
{
    this->color = color;
    RemakeTexture();
}

void Text::SetStyle(TextStyle style)
{
    this->style = style;
    RemakeTexture();
}

/*Emplaces a font in the hash map*/
void Text::EmplaceFont()
{
    std::string key = fontFile + std::to_string(fontSize); //a key is composed of the fontSize and its name
    if (Resource::assetTable.find(key) == Resource::assetTable.end())
    {
        font = TTF_OpenFont(fontFile.c_str(), fontSize);
        if (font == NULL)
            std::cerr << "ERROR! " << SDL_GetError() << std::endl;
        Resource resource(font);
        Resource::assetTable.emplace(key, resource);
    }
    else
    {
        font = Resource::assetTable.at(key).data.font;
        Resource::assetTable.at(key).userCount++;
    }
}

void Text::SetFontSize(int fontSize)
{
    Resource::assetTable.at(fontFile+std::to_string(this->fontSize)).userCount--;
    this->fontSize = fontSize;
    EmplaceFont();
    if (font != NULL)
        RemakeTexture();
}

void Text::RemakeTexture()
{
    SDL_Surface *surface;
    switch(style)
    {
        case TEXT_SOLID:
            surface = TTF_RenderText_Solid(font, text.c_str(), color);
            break;
        case TEXT_SHADED:
            surface = TTF_RenderText_Shaded(font, text.c_str(), color, SDL_Color()); //empty constructor SDL_COLOR() returns black
            break;
        case TEXT_BLENDED:
            surface = TTF_RenderText_Blended (font, text.c_str(), color);
            break;
        default:
            std::cerr << "Error! Unknown style!" << std::endl;
    }
    texture = SDL_CreateTextureFromSurface (Game::GetInstance().GetRenderer(), surface);
    SDL_FreeSurface (surface);
    int width, height;
    SDL_QueryTexture(texture, 0, 0, &width, &height);
    box.SetRect(box.GetPoint(), width, height);
}
