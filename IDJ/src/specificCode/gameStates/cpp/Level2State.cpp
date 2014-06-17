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
    bg.Open("img/level2/background.png");
    EmplaceInitialObjects();
}

Level2State::~Level2State()
{
    // TODO Auto-generated destructor stub
}

void Level2State::Update(float dt)
{
    Input();
    UpdateArray(dt);
    Camera::Update(dt);
}

void Level2State::Render()
{
    bg.Render(-Camera::pos.GetX(), -Camera::pos.GetY());
    tileMap.RenderLayer(0, Camera::pos.GetX(), Camera::pos.GetY());
}

void Level2State::EmplaceInitialObjects()
{

}

void Level2State::Input()
{
    InputManager &im = InputManager::GetInstance();
    if (im.ShouldQuit()) requestQuit = true;
}
