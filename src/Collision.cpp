#include "../include/Collision.h"

void Collision::checkCollision(Player& player, Platform* platform)
{
    if (player.getBoundingBox().getGlobalBounds().intersects(platform->getPlatform().getGlobalBounds()))
    {
        player.setIsJumping(true);
        player.setIsFalling(false);
    }
}