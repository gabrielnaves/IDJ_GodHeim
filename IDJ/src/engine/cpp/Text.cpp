/*
 * Text.cpp
 *
 *  Created on: May 4, 2014
 *      Author: Gabriel Naves
 */

#include "../include/Text.h"

std::unordered_map<std::string, Resource> Text::assetTable;

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

    std::string key = fontFile + std::to_string(fontSize);
    if (assetTable.find(key) == assetTable.end())
    {
        font = TTF_OpenFont(fontFile.c_str(), fontSize);
        if (font == NULL)
            std::cerr << "ERROR! " << SDL_GetError() << std::endl;
        Resource resource(font);
        assetTable.emplace(key, resource);
    }
    else
    {
        font = assetTable.at(key).data.font;
        assetTable.at(key).userCount++;
    }
    if (font != NULL)
        RemakeTexture();
}

Text::~Text()
{
    assetTable.at(fontFile+std::to_string(fontSize)).userCount--;
    if (texture != NULL)
        SDL_DestroyTexture(texture);
}

void Text::Render(int cameraX, int cameraY)
{
    SDL_Rect clipRect, dstrect;
    dstrect.x = box.GetX() - cameraX, clipRect.x = 0;
    dstrect.y = box.GetY() - cameraY, clipRect.x = 0;
    dstrect.w = clipRect.w = box.GetW(), clipRect.w = box.GetW();
    dstrect.h = box.GetH(), clipRect.h = box.GetH();
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

void Text::SetFontSize(int fontSize)
{
    assetTable.at(fontFile+std::to_string(this->fontSize)).userCount--;
    this->fontSize = fontSize;

    std::string key = fontFile + std::to_string(fontSize);
    if (assetTable.find(key) == assetTable.end())
    {
        font = TTF_OpenFont(fontFile.c_str(), fontSize);
        if (font == NULL)
            std::cerr << "ERROR! " << SDL_GetError() << std::endl;
        Resource resource(font);
        assetTable.emplace(key, resource);
    }
    else
    {
        font = assetTable.at(key).data.font;
        assetTable.at(key).userCount++;
    }
    if (font != NULL)
        RemakeTexture();
}

void Text::Clear()
{
    std::vector<std::string> filesToErase;
    for (auto it = assetTable.begin(); it != assetTable.end(); ++it)
        if (it->second.userCount == 0)
        {
            TTF_CloseFont(it->second.data.font); // If a texture is allocated, destroy it.
            filesToErase.push_back(it->first);
        }
    for (int i = 0; i < (int)filesToErase.size(); i++)
        assetTable.erase(filesToErase[i]);
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
            surface = TTF_RenderText_Shaded(font, text.c_str(), color, SDL_Color());
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
