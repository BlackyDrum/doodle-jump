#include "../include/Collision.h"

bool Collision::checkPlatformCollision(Player& player, Platform* platform)
{
    if (player.getBoundingBox().getGlobalBounds().intersects(platform->getPlatform().getGlobalBounds()))
        return true;

    return false;
}