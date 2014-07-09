/*
 * Credits.cpp
 *
 *  Created on: Jul 8, 2014
 *      Author: Gabriel Naves
 */

#include "../include/Credits.h"

Credits::Credits()
{
    sp.Open("img/credits/creditos.png");
    music.Open("audio/credits/CREDITOS.mp3");
    music.Play(-1);
}

void Credits::Update(float dt)
{
    InputManager &im = InputManager::GetInstance();
    if (im.ShouldQuit()) requestQuit = true;
    if (im.KeyPress(ESCAPE_KEY) or im.KeyPress(SPACE_KEY))
    {
        requestDelete = true;
        Game::GetInstance().ResetWindowSize(574, 600);
        Game::GetInstance().Push(new TitleState());
    }
}

void Credits::Render()
{
    sp.Render(0, 0);
}
