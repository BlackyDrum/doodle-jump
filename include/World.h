#ifndef _WORLD_H_
#define _WORLD_H_

#include "Globals.h"

#include "Platform.h"
#include "Player.h"

class World
{
public:
	World();

	~World();

	bool loadAssets();

	void setup();

	void moveBackground();

	void updateView(sf::RenderWindow&, Player&);

	void update(sf::Sprite);

	std::pair<sf::Sprite, sf::Sprite> getBackgrounds() const { return m_backgrounds; }
	sf::View getView() const { return m_view; }
	std::vector<Platform*> getPlatforms() const { return m_platforms; }

	void setView(sf::View view) { m_view = view; }
private:
	sf::Texture m_backgroundTexture;
	std::pair<sf::Sprite, sf::Sprite> m_backgrounds;

	sf::View m_view;

	std::vector<Platform*> m_platforms;

	float m_highestPlatformPosition;
};

#endif