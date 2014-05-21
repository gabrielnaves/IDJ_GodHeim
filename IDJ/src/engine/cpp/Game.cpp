/*
 * Game.cpp
 *
 *  Created on: May 3, 2014
 *      Author: Gabriel Naves
 */

#include "../include/Game.h"

Game* Game::instance = NULL;
std::stack<std::unique_ptr<State>> Game::stateStack;

/**
 * Initializes the SDL components, as well as some other variables.
 * @param title The title of the window.
 * @param width The width of the window.
 * @param height The height of the window.
 */
Game::Game(std::string title, int width, int height)
{
    if (Game::instance == NULL) instance = this;
    else std::cerr << "ERROR! Instance not NULL!" << std::endl, exit(1);

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) != 0)
        std::cerr << SDL_GetError() << std::endl, exit (1);

    IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF);

    window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_MAXIMIZED);

    renderer  = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (window == NULL || renderer == NULL)
        std::cerr << "ERROR! Could not create window and/or renderer!" << std::endl, exit (1);

    Mix_Init(MIX_INIT_FLAC | MIX_INIT_OGG | MIX_INIT_FLUIDSYNTH | MIX_INIT_MP3 |
             MIX_INIT_MOD | MIX_INIT_MODPLUG);

    if (Mix_OpenAudio (MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) != 0)
        std::cerr << SDL_GetError() << std::endl, exit(1);

    if (TTF_Init() != 0)
        std::cerr << SDL_GetError() << std::endl, exit(1);

    srand(time(NULL));
    frameStart = SDL_GetTicks();
    dt = 0;
    storedState  = NULL;
}

/**
 * Destroys the renderer and the window,
 * and closes SDL_Image and SDL.
 */
Game::~Game()
{
    IMG_Quit();
    Mix_CloseAudio();
    Mix_Quit();
    TTF_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

SDL_Renderer* Game::GetRenderer()
{
    return renderer;
}

Game& Game::GetInstance()
{
    return *instance;
}

State& Game::GetCurrentState()
{
    return *stateStack.top();
}

/**
 * Stores the state given at a temporary pointer. The state
 * will be stored on the stack at the beggining of the next
 * frame.
 */
void Game::Push(State* state)
{
    storedState = state;
}

/**
 * Main game loop. Calculates the time between frames,
 * updates the game state and renders the game.
 */
void Game::Run()
{
    stateStack.emplace(storedState);
    storedState = NULL;
    while (!stateStack.top()->RequestedQuit())
    {
        CalculateDeltaTime();
        InputManager::GetInstance().Update();
        if (ManageStates() == 1) break; // If there are no states on stateStack, break.
        stateStack.top()->Update(dt);
        stateStack.top()->Render();
        SDL_RenderPresent(renderer);
        SDL_Delay(33);
    }
    while (stateStack.size()>0)
        stateStack.pop();
    Resource::Clear();
}

/**
 * Calculates the elapsed time between frames, in seconds.
 */
void Game::CalculateDeltaTime()
{
    dt = SDL_GetTicks() - frameStart;
    dt = dt / 1000;
    frameStart = SDL_GetTicks();
}

/**
 * Manages the states on stateStack. Checks if the current state
 * wants to be deleted and adds stored states if any.
 * If there are no states on the stack, returns 1.
 */
int Game::ManageStates()
{
    if (stateStack.top()->RequestedDelete())
    {
        stateStack.pop();
        Resource::Clear();
    }
    if (storedState)
    {
        stateStack.emplace(storedState);
        storedState = NULL;
    }
    if (stateStack.size() == 0)
        return 1;
    return 0;
}
