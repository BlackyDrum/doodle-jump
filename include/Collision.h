#ifndef _COLLISION_H_
#define _COLLISION_H_

#include "Globals.h"

#include "Player.h"
#include "Platform.h"

class Collision
{
public:
	// Check collision with green platforms
	static bool checkPlatformCollision(Player&, Platform*);

	// Check collision with other tiles, e.g trampoline feather, ...
	static bool checkTileCollision(Player&, sf::Sprite);
private:
	Collision() = default;
};

#endif