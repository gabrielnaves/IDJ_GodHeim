/*
 * Main.cpp
 *
 *  Created on: Mar 22, 2014
 *      Author: Gabriel Naves
 */

#include "engine/include/Game.h"
#include "specificCode/gameStates/include/Level1State.h"
#include "specificCode/gameStates/include/TitleState.h"

int main(int argc, char** argv)
{
	Game game("Godheim", 574, 600);
	game.Push(new TitleState());
	game.Run();
	return 0;
}
