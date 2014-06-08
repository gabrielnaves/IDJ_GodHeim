/*
 * Level1State.cpp
 *
 *  Created on: May 19, 2014
 *      Author: Gabriel Naves
 *              Icaro Mota
 */

#include "../include/Level1State.h"

Level1State::Level1State() : State(), tileSet(55,55,"img/firstLevelTiles.png"),
                             tileMap("map/firstLevel.txt", &tileSet),
                             movementMap("map/firstLevel.txt", tileSet)
{
    bg.Open("img/background primeira fase tamanho total.png");
    rochas.Open("img/rochas.png");

    objectArray.emplace_back(new Stairs());
    objectArray.emplace_back(new Loki(70,100, movementMap));
    objectArray.emplace_back(new Thor(20,100, movementMap));
    Barrier *barrier = new Barrier();
    Camera::Follow(barrier, true, 0, 0, tileMap.GetWidth()*tileSet.GetTileWidth() - Game::GetInstance().GetWindowWidth(),
                   tileMap.GetHeight()*tileSet.GetTileHeight() - Game::GetInstance().GetWindowHeight());
    objectArray.emplace_back(barrier);
}

Level1State::~Level1State()
{
    // TODO Auto-generated destructor stub
}

void Level1State::Update(float dt)
{
    Input();
    UpdateArray(dt);
    ChecksForCollisions();
    ErasesDeadObjects();
    Camera::Update(dt);
}

void Level1State::Render()
{
    bg.Render(-Camera::pos.GetX(),-Camera::pos.GetY());
    rochas.Render(-Camera::pos.GetX(),-Camera::pos.GetY());
    tileMap.RenderLayer(0,+Camera::pos.GetX(), +Camera::pos.GetY());
    RenderArray();
    tileMap.RenderLayer(1,+Camera::pos.GetX(), +Camera::pos.GetY());
    //brokenHouse.RenderFront();
}

void Level1State::Input()
{
    if (InputManager::GetInstance().ShouldQuit())
        requestQuit = true;
}

/*Sees if any objects collided*/
void Level1State::ChecksForCollisions(){
    for(unsigned int i = 0; i<objectArray.size()-1; i++)
    {
        for (unsigned int j=i+1;j<objectArray.size();j++)
        {
            if (Collision::IsColliding(objectArray[j]->box, objectArray[i]->box,
                                       objectArray[j]->rotation*2*M_PI/360, objectArray[i]->rotation*2*M_PI/360))
            {
               objectArray[j]->NotifyCollision(*objectArray[i]);
               objectArray[i]->NotifyCollision(*objectArray[j]);
            }
        }
    }
}

void Level1State::ErasesDeadObjects(){
    for (unsigned int i=0;i<objectArray.size();i++){
        if (objectArray[i]->IsDead()) {
            objectArray.erase(objectArray.begin()+i);
            i--;
        }
    }
}
