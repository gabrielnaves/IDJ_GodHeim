/*
 * Level1State.cpp
 *
 *  Created on: May 19, 2014
 *      Author: Gabriel Naves
 *              Icaro Mota
 */

#include "../include/Level1State.h"

Level1State::Level1State() : State(), tileSet(55,55,"img/level1/level1Tiles.png"),
                             tileMap("map/firstLevel.txt", &tileSet),
                             movementMap("map/firstLevelMovementMap.txt", tileSet),
                             brokenHouse(500, 320)
{
    bg.Open("img/level1/level1Background2.png");
    rochas.Open("img/level1/rocks.png");
    EmplaceInitialObjects();
    Follow("Barrier");
    outsideMusic.Open("audio/SOUNDTRACK MODE/Fase 1/Fase 1 (Parte superior) - Eber Filipe.mp3");
    caveMusic.Open("audio/SOUNDTRACK MODE/Fase 1/Subsolo Fase 1.mp3");
    outsideMusic.Play(-1);
    outsideMusicPlaying = true;
}

Level1State::~Level1State()
{
}

void Level1State::EmplaceInitialObjects()
{
    objectArray.emplace_back(new Stairs("img/objects/stairs.png",605,440));
    objectArray.emplace_back(new Stairs("img/objects/stairs.png",390,550));
    objectArray.emplace_back(new Spikes("img/objects/spikes.png",385,2200));
    objectArray.emplace_back(new Loki(70,100, movementMap));
    objectArray.emplace_back(new Thor(20,100, movementMap));
    objectArray.emplace_back(new Bridge(220, 330));
    objectArray.emplace_back(new Goat(800, 305));
    objectArray.emplace_back(new Barrier());
}

void Level1State::Follow(std::string object)
{
    for (int i = 0; i < (int)objectArray.size(); i++)
        if (objectArray[i]->Is(object))
            Camera::Follow(&(*objectArray[i]), true, 0, 0, tileMap.GetWidth()*tileSet.GetTileWidth() - Game::GetInstance().GetWindowWidth(),
                           tileMap.GetHeight()*tileSet.GetTileHeight() - Game::GetInstance().GetWindowHeight());
}

void Level1State::Update(float dt)
{
    Input();
    UpdateArray(dt);
    brokenHouse.Update(dt);
    ChecksForCollisions();
    ErasesDeadObjects();
    Camera::Update(dt);
    UpdateMusic(dt);
}

void Level1State::Render()
{
    bg.Render(-Camera::pos.GetX(),-Camera::pos.GetY());
    rochas.Render(-Camera::pos.GetX(),-Camera::pos.GetY());
    tileMap.RenderLayer(0,+Camera::pos.GetX(), +Camera::pos.GetY());
    brokenHouse.RenderBack();
    RenderArray();
    if (!tileMap.HasTile(Loki::characterLoki->box.Center().GetX(), Loki::characterLoki->box.Center().GetY(), 1) &&
        !tileMap.HasTile(Thor::characterThor->box.Center().GetX(), Thor::characterThor->box.Center().GetY(), 1))
        tileMap.RenderLayer(1,+Camera::pos.GetX(), +Camera::pos.GetY());
    brokenHouse.RenderFront();
}

void Level1State::Input()
{
    if (InputManager::GetInstance().ShouldQuit())
        requestQuit = true;
}

/*Sees if any objects collided*/
void Level1State::ChecksForCollisions()
{
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

void Level1State::ErasesDeadObjects()
{
    for (unsigned int i = 0; i < objectArray.size(); i++)
        if (objectArray[i]->IsDead())
            objectArray.erase(objectArray.begin()+i), i++;
}

void Level1State::UpdateMusic(float dt)
{
    Point barrierPos;

    // Finds the position of the center of the barrier
    for (int i = 0; i < (int)objectArray.size(); i++)
        if (objectArray[i]->Is("Barrier"))
            barrierPos = objectArray[i]->box.Center();

    if (barrierPos.GetX() >= 550 && outsideMusicPlaying)
    {
        fadeTimer.Update(dt);
        if (fadeTimer.Get() >= 2)
        {

        }
    }
}
