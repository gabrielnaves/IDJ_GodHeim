/*
 * Level1State.cpp
 *
 *  Created on: May 19, 2014
 *      Author: Gabriel Naves
 *              Icaro Mota
 */

#include "../include/Level1State.h"

Level1State::Level1State() : State(), tileSet(55,55,"img/level1/level1Tiles.png"),
                             tileMap("map/level1.txt", &tileSet),
                             movementMap("map/level1MovementMap.txt", tileSet)
{
    bg.Open("img/level1/level1Background2.png");
    rochas.Open("img/level1/rocks.png");
    EmplaceInitialObjects();
    Follow("Barrier");
    SelectMusic();
    outsideMusic->Play(-1);
    musicPlaying = true;
    showingCave = false;
}

/**
 * Selects the musics of the level according to the soundtrack mode
 */
void Level1State::SelectMusic()
{
    if (StateData::soundMode == "Normal")
    {
        outsideMusic = new Music("audio/SOUNDTRACK MODE/Fase 1/outside_music.mp3");
        caveMusic = new Music("audio/SOUNDTRACK MODE/Fase 1/cave_music.mp3");
    }
    if (StateData::soundMode == "8bits")
    {
        outsideMusic = new Music("audio/8 bit MODE/outside_music.mp3");
        caveMusic = new Music("audio/8 bit MODE/cave_music(eff).mp3");
    }
    if (StateData::soundMode == "SNES")
    {
        outsideMusic = new Music("audio/Forever SNES MODE/outside_music.mp3");
        caveMusic = new Music("audio/Forever SNES MODE/cave_music.mp3");
    }
}

Level1State::~Level1State()
{
	objectArray.clear();
}

void Level1State::EmplaceInitialObjects()
{
    objectArray.emplace_back(new Stairs("img/objects/stairs.png",605,440));
    objectArray.emplace_back(new Stairs("img/objects/stairs.png",280,550));
    objectArray.emplace_back(new Stairs("img/objects/stairsBig.png",110,1650));
    objectArray.emplace_back(new Gate("img/level1/grade.png",7*55,24.5*55));
    objectArray.emplace_back(new Rope("img/objects/rope.png",1100,500,false));
    objectArray.emplace_back(new Switch(1250,550,"img/objects/button.png","img/objects/buttonPressed.png",
            &(*objectArray[objectArray.size()-1])));
    objectArray.emplace_back(new Rope("img/objects/rope.png", 950, 495));
    objectArray.emplace_back(new Rope("img/objects/smallRope.png",550,1045));
    objectArray.emplace_back(new BrokenHouseBack(500, 320));
    objectArray.emplace_back(new Loki(70,220, movementMap));
    objectArray.emplace_back(new Thor(30,220, movementMap));
    objectArray.emplace_back(new Bridge(220, 330));
    objectArray.emplace_back(new BrokenHouseFront(500, 320));
    objectArray.emplace_back(new Item(355,520,"img/items/lokifire.png", "LokiFire", false, true));
    objectArray.emplace_back(new Item(1150,300,"img/items/lokifly.png", "LokiEagle", false, true));
    objectArray.emplace_back(new Item(1220,590,"img/items/thorbelt.png", "ThorBelt", true, false));
    objectArray.emplace_back(new Item(865,2000,"img/items/thorhammer.png", "ThorHammer", true, false));
    objectArray.emplace_back(new Spikes("img/objects/spikes.png",385,2200));
    objectArray.emplace_back(new Plants("img/level1/plants/5.png",255,510));
    objectArray.emplace_back(new Plants("img/level1/plants/3.png",260,525));
    objectArray.emplace_back(new Plants("img/level1/plants/10.png",410,530));
    objectArray.emplace_back(new Plants("img/level1/plants/9.png",390,530));
    objectArray.emplace_back(new Plants("img/level1/plants/4.png",395,515));
    objectArray.emplace_back(new Plants("img/level1/plants/1.png",395,485));
    objectArray.emplace_back(new Plants("img/level1/plants/10.png",365,530));
    objectArray.emplace_back(new Plants("img/level1/plants/6.png",365,515));
    objectArray.emplace_back(new Plants("img/level1/plants/2.png",325,525));
    objectArray.emplace_back(new Plants("img/level1/plants/7.png",285,525));
    objectArray.emplace_back(new Plants("img/level1/plants/10.png",450,425));
    objectArray.emplace_back(new Plants("img/level1/plants/5.png",425,405));
    objectArray.emplace_back(new Plants("img/level1/plants/2.png",420,430));
    objectArray.emplace_back(new Plants("img/level1/plants/3.png",425,425));
    objectArray.emplace_back(new Plants("img/level1/plants/9.png",480,425));
    objectArray.emplace_back(new Plants("img/level1/plants/10.png",500,425));
    objectArray.emplace_back(new Plants("img/level1/plants/10.png",530,425));
    objectArray.emplace_back(new Plants("img/level1/plants/4.png",530,405));
    objectArray.emplace_back(new Plants("img/level1/plants/10.png",600,420));
    objectArray.emplace_back(new Plants("img/level1/plants/6.png",570,410));
    objectArray.emplace_back(new Plants("img/level1/plants/7.png",500,415));
    objectArray.emplace_back(new Plants("img/level1/plants/1.png",460,415));
    objectArray.emplace_back(new Plants("img/level1/plants/9.png",525,320));
    objectArray.emplace_back(new Plants("img/level1/plants/10.png",530,320));
    objectArray.emplace_back(new Plants("img/level1/plants/10.png",580,375));
    objectArray.emplace_back(new Plants("img/level1/plants/9.png",640,375));
    objectArray.emplace_back(new Plants("img/level1/plants/10.png",610,375));
    objectArray.emplace_back(new PlantBarrier("img/objects/plant.png",870,880));
    objectArray.emplace_back(new Rock("img/objects/pedra.png",1045,1045));
    objectArray.emplace_back(new StoneBlock("img/objects/pedra.png",850,1540));
    objectArray.emplace_back(new Goat(800, 310));
    objectArray.emplace_back(new Wolf(75, 744, 565, movementMap));
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
    if (Thor::characterThor != NULL && Loki::characterLoki != NULL && Barrier::barrier != NULL)
    {
        UpdateArray(dt);
        ChecksForCollisions();
        ErasesDeadObjects();
    }
    else
    	EndGame(dt);
    if (Barrier::barrier == NULL) Camera::Unfollow();

    Camera::Update(dt);
    UpdateMusic(dt);

    if (StageClear()) NextLevel();
}

void Level1State::EndGame(float dt)
{
	endGame.Update(dt);
	if (endGame.Get()>=1.5)
	{
		requestDelete = true;
		caveMusic->Stop();
        Game::GetInstance().ResetWindowSize(360,275);
		Game::GetInstance().Push(new EndState());
	}
}


bool Level1State::StageClear()
{
	return (  	 ((Thor::characterThor->box.Center().GetX() > 1210) && (Thor::characterThor->box.Center().GetY() > 2150)
			   && (Loki::characterLoki->box.Center().GetX() > 1210) && (Loki::characterLoki->box.Center().GetY() > 2150)) ? true : false);
}


void Level1State::NextLevel()
{
	requestDelete = true;
	caveMusic->Stop();
	Game::GetInstance().Push(new Level2State());
}


void Level1State::Render()
{
    bg.Render(-Camera::pos.GetX(),-Camera::pos.GetY());
    rochas.Render(-Camera::pos.GetX(),-Camera::pos.GetY());
    tileMap.RenderLayer(0,+Camera::pos.GetX(), +Camera::pos.GetY());
    RenderArray();
    if (Loki::characterLoki != NULL && Thor::characterThor != NULL)
    {
        if (!tileMap.HasTile(Loki::characterLoki->box.Center().GetX(), Loki::characterLoki->box.Center().GetY(), 1) &&
            !tileMap.HasTile(Thor::characterThor->box.Center().GetX(), Thor::characterThor->box.Center().GetY(), 1))
            tileMap.RenderLayer(1,+Camera::pos.GetX(), +Camera::pos.GetY()), showingCave = false;
        else showingCave = true;
    }
    else if (!showingCave) tileMap.RenderLayer(1,+Camera::pos.GetX(), +Camera::pos.GetY());
	if (Thor::characterThor != NULL) Thor::characterThor->RenderHP();
	if (Loki::characterLoki != NULL) Loki::characterLoki->RenderHP();
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
            objectArray.erase(objectArray.begin()+i), i--;
}

void Level1State::UpdateMusic(float dt)
{
    if (Barrier::barrier == NULL) return;
    CheckMusic(605, 660, 440, 550);
    CheckMusic(385, 440, 550, 660);
}

void Level1State::CheckMusic(float lowerX, float upperX, float lowerY, float upperY)
{
    Point barrierPos(Barrier::barrier->box.Center());
    if (barrierPos.GetX() >= lowerX && barrierPos.GetX() <= upperX)
    {
        if (barrierPos.GetY() < lowerY && !musicPlaying)
        {
            delete outsideMusic;
            Resource::Clear();
            SelectMusic();
            outsideMusic->Play(-1);
            musicPlaying = true;
        }
        if (barrierPos.GetY() >= lowerY && barrierPos.GetY() <= upperY)
        {
            if (musicPlaying)
            {
                outsideMusic->Stop(0.2);
                musicPlaying = false;
            }
        }
        if (barrierPos.GetY() > upperY && !musicPlaying)
        {
            delete caveMusic;
            Resource::Clear();
            SelectMusic();
            caveMusic->Play(-1);
            musicPlaying = true;
        }
    }
}
