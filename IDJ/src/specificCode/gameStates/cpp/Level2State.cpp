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
    Follow("Barrier");
    SelectMusic();
    music->Play(-1);
}

Level2State::~Level2State()
{
    delete lavaCircle;
}

/**
 * Selects the musics of the level according to the soundtrack mode
 */
void Level2State::SelectMusic()
{
    if (StateData::soundMode == "Normal")
        music = new Music("audio/SOUNDTRACK MODE/Fase 2/Fire Stage 1parte -Eber Filipe.mp3");
    if (StateData::soundMode == "8bits")
        music = new Music("audio/8 bit MODE/LAVA STAGE parte 2 (HOTHOTPIMENTA) .mp3");
    if (StateData::soundMode == "SNES")
        music = new Music("audio/Forever SNES MODE/Stage two (DONKEY KONG style) Parte 1.mp3");
}

void Level2State::Update(float dt)
{
    Input();
    lavaCircle->Update(dt);
    if (Thor::characterThor != NULL && Loki::characterLoki != NULL && Barrier::barrier != NULL)
    {
        UpdateArray(dt);
        ChecksForCollisions();
        ErasesDeadObjects();
    }
    if (Barrier::barrier == NULL) Camera::Unfollow();
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
    objectArray.emplace_back(new Loki(1175,100, movementMap));
    objectArray.emplace_back(new Thor(1225,100, movementMap));
    objectArray.emplace_back(new Barrier());
    objectArray.emplace_back(new Lava(0, 1430));
}

void Level2State::Input()
{
    InputManager &im = InputManager::GetInstance();
    if (im.ShouldQuit()) requestQuit = true;
}

void Level2State::Follow(std::string object)
{
    for (int i = 0; i < (int)objectArray.size(); i++)
        if (objectArray[i]->Is(object))
            Camera::Follow(&(*objectArray[i]), true, 0, 0, tileMap.GetWidth()*tileSet.GetTileWidth() - Game::GetInstance().GetWindowWidth(),
                           tileMap.GetHeight()*tileSet.GetTileHeight() - Game::GetInstance().GetWindowHeight());
}

void Level2State::ChecksForCollisions()
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

void Level2State::ErasesDeadObjects()
{
    for (unsigned int i = 0; i < objectArray.size(); i++)
        if (objectArray[i]->IsDead())
            objectArray.erase(objectArray.begin()+i), i--;

}
