#ifndef _COLLISION_H_
#define _COLLISION_H_

#include "Globals.h"

#include "Player.h"
#include "Platform.h"

class Collision
{
public:
	static bool checkPlatformCollision(Player&, Platform*);

	static bool checkFeatherCollision(Player&, sf::Sprite);
private:
	Collision() = default;
};

#endif