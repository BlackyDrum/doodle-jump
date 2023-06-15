#include "../include/World.h"

World::World()
{
	m_platformTexture.loadFromFile("assets/textures/game-tiles.png");

	m_platformGap = 100;

	for (int i = 0; i < 20; i++)
	{
		Platform* p = new Platform;
		p->getPlatform().setTexture(m_platformTexture);
		p->getPlatform().setTextureRect(sf::IntRect(0, 0, 58, 16));

		float x = rand() % (SCREEN_WIDTH - p->getPlatform().getTextureRect().width);
		p->setup(sf::Vector2f(x, -i * m_platformGap));

		m_highestPlatformPosition = -i * m_platformGap;

		m_platforms.push_back(p);
	}

}

World::~World()
{
	for (auto& p : m_platforms)
		delete p;
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

	m_view.move(0, SCREEN_HEIGHT / 2 * -1.0);
}

void World::moveBackground()
{
	//m_view.setCenter(m_view.getCenter().x, player.getPosition().y);

	if (m_backgrounds.first.getPosition().y > m_view.getCenter().y + SCREEN_HEIGHT / 2)
		m_backgrounds.first.setPosition(0, m_backgrounds.second.getPosition().y - SCREEN_HEIGHT);

	if (m_backgrounds.second.getPosition().y > m_view.getCenter().y + SCREEN_HEIGHT / 2)
		m_backgrounds.second.setPosition(0, m_backgrounds.first.getPosition().y - SCREEN_HEIGHT);
}

void World::updateView(sf::RenderWindow& window, Player& player)
{
	sf::View v = window.getView();
	v.setCenter(SCREEN_WIDTH / 2, player.getPlayer().getPosition().y);

	float y = player.getPlayer().getPosition().y;

	if (player.getHighestPosition() >= y)
		m_view = v;

	window.setView(m_view);
}

void World::update(sf::Sprite player)
{
	for (int i = 0; i < m_platforms.size(); i++)
	{
		if (player.getPosition().y < m_platforms[i]->getPlatform().getPosition().y - SCREEN_HEIGHT / 2)
		{
			delete m_platforms[i];
			m_platforms.erase(m_platforms.begin() + i);
		}
	}

	if (player.getPosition().y - SCREEN_HEIGHT / 2 < m_highestPlatformPosition)
	{
		Platform* p = new Platform;
		p->getPlatform().setTexture(m_platformTexture);
		p->getPlatform().setTextureRect(sf::IntRect(0, 0, 58, 16));

		float x = rand() % (SCREEN_WIDTH - p->getPlatform().getTextureRect().width);
		p->setup(sf::Vector2f(x, m_highestPlatformPosition - m_platformGap));

		m_highestPlatformPosition = m_highestPlatformPosition - m_platformGap;

		m_platforms.push_back(p);
	}	
}