#ifndef _GAME_H_
#define _GAME_H_

#include "Globals.h"

#include "Renderer.h"
#include "Settings.h"
#include "World.h"
#include "Player.h"
#include "Platform.h"
#include "Collision.h"
#include "Score.h"

class Game
{
public:
	static void run();
private:
	Game() = default;
};

#endif