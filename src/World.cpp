#include "../include/World.h"

World::World(b2Vec2 gravity)
{
	m_gravity = gravity;
	m_world = new b2World(gravity);
}

World::~World()
{
	delete m_world;
}

bool World::loadAssets()
{
	if (!m_backgroundTexture.loadFromFile("assets/textures/background.png"))
		return false;

	m_backgrounds.first.setTexture(m_backgroundTexture);
	m_backgrounds.second.setTexture(m_backgroundTexture);

	return true;
}

void World::setup()
{
	m_backgrounds.second.setPosition(0, SCREEN_HEIGHT * -1.0);

	m_view.setSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	m_view.setCenter(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
}

void World::moveView(sf::RenderWindow& window, sf::Sprite player)
{
	window.setView(m_view);

	if (m_backgrounds.first.getPosition().y > m_view.getCenter().y + SCREEN_HEIGHT / 2)
		m_backgrounds.first.setPosition(0, m_backgrounds.second.getPosition().y - SCREEN_HEIGHT);

	if (m_backgrounds.second.getPosition().y > m_view.getCenter().y + SCREEN_HEIGHT / 2)
		m_backgrounds.second.setPosition(0, m_backgrounds.first.getPosition().y - SCREEN_HEIGHT);
}