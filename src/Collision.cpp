#include "../include/Collision.h"

bool Collision::checkPlatformCollision(Player& player, Platform* platform)
{
    if (player.getBoundingBox().getGlobalBounds().intersects(platform->getPlatform().getGlobalBounds()) && player.getIsFalling())
        return true;

    return false;
}

bool Collision::checkTileCollision(Player& player, sf::Sprite tile)
{
    if (player.getBoundingBox().getGlobalBounds().intersects(tile.getGlobalBounds()) && player.getIsFalling())
        return true;

    return false;
}