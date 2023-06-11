#ifndef _COLLISION_H_
#define _COLLISION_H_

#include "Globals.h"

#include "Player.h"
#include "Platform.h"

class Collision
{
public:
	static void checkPlatformCollision(Player&, Platform*);
private:
	Collision() = default;
};

#endif