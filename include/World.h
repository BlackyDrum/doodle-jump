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

	void setFeatherTexture();

	void setTrampolineTexture();

	std::pair<sf::Sprite, sf::Sprite> getBackgrounds() const { return m_backgrounds; }
	sf::Sprite getFeather() const { return m_feather; }
	sf::Sprite getTrampoline() const { return m_trampoline; }
	sf::Sprite getMovablePlatform() const { return m_movablePlatform; }
	sf::View& getView() { return m_view; }
	std::vector<Platform*> getPlatforms() const { return m_platforms; }
	std::vector<Platform*> getBrokenPlatforms() const { return m_brokenPlatforms; }
	std::vector<bool> getBrokenPlatformIsFalling() const { return m_brokenPlatformIsFalling; }

	void setView(sf::View view) { m_view = view; }
	void setBrokenPlatformIsFalling(int index) { m_brokenPlatformIsFalling[index] = true; }
private:
	sf::Texture m_backgroundTexture, m_tiles;
	std::pair<sf::Sprite, sf::Sprite> m_backgrounds;

	sf::Sprite m_feather;
	sf::Sprite m_trampoline;
	sf::Sprite m_movablePlatform;

	sf::IntRect m_platformRect, m_brokenPlatformRect, m_brokenPlatformDownRect;
	sf::IntRect m_featherDefaultRect, m_featherJumpedRect;
	sf::IntRect m_trampolineDefaultRect, m_trampolineJumpedRect;
	sf::IntRect m_movablePlatformRect;

	sf::View m_view;

	std::vector<Platform*> m_platforms;
	std::vector<Platform*> m_brokenPlatforms;

	std::vector<bool> m_brokenPlatformIsFalling;

	float m_highestPlatformPosition, m_highestBrokenPlatformPosition;

	int m_platformGap;
	int m_trampolineSpawnRate, m_movablePlatformSpawnRate;
	int m_movablePlatformSpeed;

	enum Direction
	{
		LEFT,
		RIGHT
	};

	Direction m_movablePlatformDirection;

	void createPlatforms(sf::Sprite);

	void moveBrokenPlatformDown();

};

#endif