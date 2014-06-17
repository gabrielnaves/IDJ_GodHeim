/*
 * Level2State.cpp
 *
 *  Created on: Jun 17, 2014
 *      Author: Gabriel Naves
 */

#include "../include/Level2State.h"

Level2State::Level2State() : State(), tileSet(55,55,"img/level2/level2Tiles.png"),
                             tileMap("map/level2.txt", &tileSet),
                             movementMap("map/level2MovementMap.txt", tileSet)
{
    bg1.Open("img/level2/background.png");
    bg2.Open("img/level2/rocks.png");
    lavaCircle = new LavaCircle(680, 900);
    tmpBlackBg.Open("img/level2/blackBackground.png");
    EmplaceInitialObjects();
}

Level2State::~Level2State()
{
    delete lavaCircle;
}

void Level2State::Update(float dt)
{
    Input();
    lavaCircle->Update(dt);
    UpdateArray(dt);
    Camera::Update(dt);
}

void Level2State::Render()
{
    tmpBlackBg.Render(0,0);
    bg1.Render(-Camera::pos.GetX(), -Camera::pos.GetY());
    lavaCircle->Render();
    bg2.Render(-Camera::pos.GetX(), -Camera::pos.GetY());
    tileMap.RenderLayer(0, Camera::pos.GetX(), Camera::pos.GetY());
    RenderArray();
}

void Level2State::EmplaceInitialObjects()
{
}

void Level2State::Input()
{
    InputManager &im = InputManager::GetInstance();
    if (im.ShouldQuit()) requestQuit = true;
}
