#include "../include/Collision.h"

bool Collision::checkPlatformCollision(Player& player, Platform* platform)
{
    if (player.getBoundingBox().getGlobalBounds().intersects(platform->getPlatform().getGlobalBounds()) && player.getIsFalling())
        return true;

    return false;
}

bool Collision::checkFeatherCollision(Player& player, sf::Sprite feather)
{
    if (player.getBoundingBox().getGlobalBounds().intersects(feather.getGlobalBounds()) && player.getIsFalling())
        return true;

    return false;
}