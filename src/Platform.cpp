#include "../include/Platform.h"

bool Platform::loadAssets()
{
	if (!m_platformTexture.loadFromFile("assets/textures/game-tiles.png"))
		return false;

	m_platform.setTexture(m_platformTexture);
	m_platform.setTextureRect(sf::IntRect(0, 0, 58, 16));

	return true;
}

void Platform::setup(sf::Vector2f position)
{
	m_platform.setPosition(position);
}