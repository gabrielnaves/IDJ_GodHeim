/*
 * Main.cpp
 *
 *  Created on: Mar 22, 2014
 *      Author: Gabriel Naves
 */

#include "engine/include/Game.h"
#include "specificCode/gameStates/include/Level1State.h"

int main(int argc, char** argv)
{
	Game game("Godheim", 1200, 650);
	game.Push(new Level1State());
	game.Run();
	return 0;
}
