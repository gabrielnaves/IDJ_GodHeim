/*
 * Level1State.cpp
 *
 *  Created on: May 19, 2014
 *      Author: Gabriel Naves
 *              Icaro Mota
 */

#include "../include/Level1State.h"

Level1State::Level1State() : State(), tileSet(55,55,"img/firstLevelTiles.png"),
                             tileMap("map/firstLevel.txt", &tileSet)
{
    tempBlackBackground.Open("img/Canvas Master.png");
    bg.Open("img/background primeira fase tamanho total.png");
    rochas.Open("img/rochas.png");

    objectArray.emplace_back(new Loki(70,100, MovementMap("map/firstLevel.txt", tileSet)));
    objectArray.emplace_back(new Thor(20,100, MovementMap("map/firstLevel.txt", tileSet)));
    Barrier *barrier = new Barrier();
    Camera::Follow(barrier);
    objectArray.emplace_back(barrier);
}

Level1State::~Level1State()
{
    // TODO Auto-generated destructor stub
}

void Level1State::Update(float dt)
{
    UpdateArray(dt);
    Camera::Update(dt);
    Input();
}

void Level1State::Render()
{
    tempBlackBackground.Render(0, 0);
    bg.Render(-Camera::pos.GetX(),-Camera::pos.GetY());
    rochas.Render(-Camera::pos.GetX(),-Camera::pos.GetY());
    tileMap.RenderLayer(0,+Camera::pos.GetX(), +Camera::pos.GetY());
    tileMap.RenderLayer(1,+Camera::pos.GetX(), +Camera::pos.GetY());
    RenderArray();
}

void Level1State::Input()
{
    if (InputManager::GetInstance().ShouldQuit() || InputManager::GetInstance().KeyPress(ESCAPE_KEY))
        requestQuit = true;
}
