/*
 * GameBase.cpp
 *
 *  Created on: Mar 21, 2014
 *      Author: Gabriel Naves
 */

#include "../include/GameBase.h"

GameBase* GameBase::instance = NULL;

/**
 * Initializes the SDL components, as well as some other variables.
 * @param title The title of the window.
 * @param width The width of the window.
 * @param height The height of the window.
 */
GameBase::GameBase(std::string title, int width, int height)
{
	if (GameBase::instance == NULL) instance = this;
	else std::cerr << "ERROR! Instance not NULL!" << std::endl, exit(1);

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER)!=0)
	{
		std::cerr << SDL_GetError() << std::endl;
		exit (1);
	}

	IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF);

	window = SDL_CreateWindow(title.c_str(),
							  SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height,
							  SDL_WINDOW_MAXIMIZED);

	renderer  = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	if (window == NULL || renderer == NULL)
	{
		std::cerr << "ERROR! Could not create window and/or renderer!" << std::endl;
		exit (1);
	}

	shouldQuit = false;
	frameStart = SDL_GetTicks();
	dt = 0;
	srand(time(NULL));
}

/**
 * Destroys the renderer and the window,
 * and closes SDL_Image and SDL.
 */
GameBase::~GameBase()
{
	IMG_Quit();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

GameBase& GameBase::GetInstance()
{
	return *instance;
}

SDL_Renderer* GameBase::GetRenderer()
{
	return renderer;
}

/**
 * Main game loop. Calculates the time between frames,
 * updates the game state and renders the game.
 */
void GameBase::Run()
{
	while (!shouldQuit)
	{
	    CalculateDeltaTime();
	    InputManager::GetInstance().Update();
	    Camera::Update(dt);
		Update();
		Render();
		SDL_RenderPresent(renderer);
		SDL_Delay(33);
	}
}

/**
 * Calculates the elapsed time between frames, in seconds.
 */
void GameBase::CalculateDeltaTime()
{
    dt = SDL_GetTicks() - frameStart;
    dt = dt / 1000;
    frameStart = SDL_GetTicks();
}

float GameBase::GetDeltaTime()
{
    return dt;
}
