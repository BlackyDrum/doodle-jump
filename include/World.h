#ifndef _WORLD_H_
#define _WORLD_H_

#include "Globals.h"

class World
{
public:
	World(b2Vec2 gravity);

	~World();

	bool loadAssets();

	void setup();

	void moveView(sf::RenderWindow&, sf::Sprite);

	std::pair<sf::Sprite, sf::Sprite> getBackgrounds() const { return m_backgrounds; }
	sf::View getView() const { return m_view; }
	b2World* getWorld() const { return m_world; }
private:
	sf::Texture m_backgroundTexture;
	std::pair<sf::Sprite, sf::Sprite> m_backgrounds;

	sf::View m_view;

	b2World* m_world;
};

#endif