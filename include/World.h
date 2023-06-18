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
	std::vector<Platform*> getBrokenPlatforms() const { return m_brokenPlatforms; }

	void setView(sf::View view) { m_view = view; }
	void setBrokenPlatformIsFalling(int index) { m_brokenPlatformIsFalling[index] = true; }
private:
	sf::Texture m_backgroundTexture, m_tiles;
	std::pair<sf::Sprite, sf::Sprite> m_backgrounds;

	sf::IntRect m_platformRect, m_brokenPlatformRect, m_brokenPlatformDownRect;

	sf::View m_view;

	std::vector<Platform*> m_platforms;
	std::vector<Platform*> m_brokenPlatforms;

	std::vector<bool> m_brokenPlatformIsFalling;

	float m_highestPlatformPosition, m_highestBrokenPlatformPosition;

	int m_platformGap;

	void createPlatforms(sf::Sprite);

	void moveBrokenPlatformDown();

};

#endif