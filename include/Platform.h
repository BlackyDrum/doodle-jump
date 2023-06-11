#ifndef _PLATFORM_H_
#define _PLATFORM_H_

#include "Globals.h"

class Platform
{
public:
	void setup(b2World*, sf::Vector2f);

	bool loadAssets();

	sf::Sprite getPlatform() const { return m_platform; }
	b2Body* getBody() { return m_body; }
private:
	sf::Texture m_platformTexture;
	sf::Sprite m_platform;

	b2Body* m_body;
};

#endif