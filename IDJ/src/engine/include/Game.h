/*
 * Game.h
 *
 *  Created on: May 3, 2014
 *      Author: Gabriel Naves
 *
 *  Description: Has the main loop of the game. Manages all the states.
 *
 */

#ifndef GAME_H_
#define GAME_H_

#include "InputManager.h"
#include "State.h"
#include "Resource.h"

class Game
{
  public:
    Game(std::string title, int width, int height);
    ~Game();

    SDL_Renderer* GetRenderer();
    static Game& GetInstance();
    static State& GetCurrentState();

    void Push(State* state);
    void Run();

    int GetWindowWidth();
    int GetWindowHeight();

  private:
    int frameStart;
    float dt;
    void CalculateDeltaTime();
    int ManageStates();

    static Game* instance;

    int windowWidth, windowHeight;
    State* storedState;
    SDL_Window* window;
    SDL_Renderer* renderer;
    static std::stack<std::unique_ptr<State>> stateStack;
};

#endif /* GAME_H_ */
