#ifndef _PLATFORM_H_
#define _PLATFORM_H_

#include "Globals.h"

class Platform
{
public:
	void setup(sf::Vector2f);

	sf::Sprite& getPlatform() { return m_platform; }
private:
	sf::Texture m_platformTexture;
	sf::Sprite m_platform;
};

#endif