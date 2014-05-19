/*
 * Game.h
 *
 *  Created on: May 3, 2014
 *      Author: Gabriel Naves
 */

#ifndef GAME_H_
#define GAME_H_

#include "InputManager.h"
#include "Camera.h"
#include "State.h"
#include "Sprite.h"
#include "Sound.h"
#include "Text.h"

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

  private:
    int frameStart;
    float dt;
    void CalculateDeltaTime();
    int ManageStates();
    void ClearResources();

    static Game* instance;

    State* storedState;
    SDL_Window* window;
    SDL_Renderer* renderer;
    static std::stack<std::unique_ptr<State>> stateStack;
};

#endif /* GAME_H_ */
