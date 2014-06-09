/*
 * State.h
 *
 *  Created on: May 3, 2014
 *      Author: Gabriel Naves
 *
 *  Description: Implements a basic interface of the behavior and communication of a state of the game
 *
 */

#ifndef STATE_H_
#define STATE_H_

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <string>
#include <iostream>
#include <vector>
#include <memory>
#include <ctime>
#include <fstream>
#include <unordered_map>
#include <queue>
#include <stack>

#include "GameObject.h"

class State
{
  public:
    State();
    virtual ~State();

    virtual void Update(float dt) = 0;
    virtual void Render() = 0;
    virtual void AddObject(GameObject* ptr);

    bool RequestedDelete();
    bool RequestedQuit();

    std::vector<std::unique_ptr<GameObject>>& GetObjectArray() {return(objectArray);}
  protected:
    bool requestDelete;
    bool requestQuit;

    virtual void UpdateArray(float dt);
    virtual void RenderArray();

    std::vector<std::unique_ptr<GameObject>> objectArray;
};

#endif /* STATE_H_ */
