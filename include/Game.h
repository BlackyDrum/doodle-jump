#ifndef _GAME_H_
#define _GAME_H_

#include "Globals.h"

#include "Renderer.h"
#include "Settings.h"
#include "World.h"


class Game
{
public:
	static void run();
private:
	Game() = default;
};

#endif