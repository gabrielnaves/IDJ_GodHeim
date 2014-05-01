/*
 * GameBase.h
 *
 *  Created on: Mar 21, 2014
 *      Author: Gabriel Naves
 */

#ifndef GAMEBASE_H_
#define GAMEBASE_H_

#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <iostream>
#include <vector>
#include <memory>
#include <ctime>
#include <fstream>
#include <unordered_map>
#include <queue>

#include "GameObject.h"
#include "InputManager.h"
#include "Camera.h"

/**
 * The GameBase class is an interface for the implementation of the
 * game. It contains the basic functions that a game should have,
 * and implements the initialization of the SDL components.
 * It implements a Singleton pattern, in order to prevent multiple
 * instantiation and to give other engine classes access to the
 * renderer and the window.
 */
class GameBase
{
  public:
	void Run();
	SDL_Renderer* GetRenderer();
	static GameBase& GetInstance();
	float GetDeltaTime();
	virtual void AddObject(GameObject* ptr) = 0;

  protected:
	GameBase(std::string title, int width, int height);
	virtual ~GameBase();
	virtual void Update() = 0;
	virtual void Render() = 0;
	bool shouldQuit;
	std::vector<std::unique_ptr<GameObject>> objectArray;

  private:
	int frameStart;
	float dt;
	void CalculateDeltaTime();

	static GameBase* instance;
	SDL_Window* window;
	SDL_Renderer* renderer;
};

#endif /* GAMEBASE_H_ */
