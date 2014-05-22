/*
 * Level1State.cpp
 *
 *  Created on: May 19, 2014
 *      Author: Gabriel Naves
 */

#include "../include/Level1State.h"

Level1State::Level1State() : State(), tileSet(55,55,"img/tiles2.png"),
                             tileMap("map/firstLevelMap.txt", &tileSet)
{
	tempBlackBackground.Open("img/Canvas Master.png");
    bg.Open("img/background primeira fase tamanho total.png");
    Loki *loki = new Loki(600,408);
    Camera::Follow(loki);
    objectArray.emplace_back(loki);
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
    tileMap.RenderLayer(0,+Camera::pos.GetX(), +Camera::pos.GetY());
    RenderArray();
}

void Level1State::Input()
{
    if (InputManager::GetInstance().ShouldQuit() || InputManager::GetInstance().KeyPress(ESCAPE_KEY))
        requestQuit = true;
}
