#include "../include/World.h"

World::World()
{
	m_tiles.loadFromFile("assets/textures/game-tiles.png");

	m_featherDefaultRect = sf::IntRect(403, 98, 18, 13);
	m_featherJumpedRect = sf::IntRect(403, 114, 18, 29);
	m_feather.setTexture(m_tiles);
	m_feather.setTextureRect(m_featherDefaultRect);

	m_platformRect = sf::IntRect(0, 0, 58, 16);
	m_brokenPlatformRect = sf::IntRect(0, 72, 61, 16);
	m_brokenPlatformDownRect = sf::IntRect(0, 115, 61,31);

	m_trampolineDefaultRect = sf::IntRect(187,97,37,15);
	m_trampolineJumpedRect = sf::IntRect(148,93,37,19);
	m_trampoline.setTexture(m_tiles);
	m_trampoline.setTextureRect(m_trampolineDefaultRect);

	m_platformGap = 100;
	m_trampolineSpawnRate = 10;

}

World::~World()
{
	for (auto& p : m_platforms)
		delete p;
	for (auto& p : m_brokenPlatforms)
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
	m_highestPlatformPosition = 0;

	int size = m_platforms.size();
	for (int i = size - 1; i >= 0; i--)
	{
		delete m_platforms[i];
		m_platforms.erase(m_platforms.begin() + i);
	}

	size = m_brokenPlatforms.size();
	for (int i = size - 1; i >= 0; i--)
	{
		delete m_brokenPlatforms[i];
		m_brokenPlatforms.erase(m_brokenPlatforms.begin() + i);
		m_brokenPlatformIsFalling.erase(m_brokenPlatformIsFalling.begin() + i);
	}

	for (int i = 0; i < 20; i++)
	{
		Platform* p = new Platform;
		p->getPlatform().setTexture(m_tiles);
		p->getPlatform().setTextureRect(m_platformRect);

		float x = rand() % (SCREEN_WIDTH - p->getPlatform().getTextureRect().width);
		p->setup(sf::Vector2f(x, -i * m_platformGap));

		m_highestPlatformPosition = -i * m_platformGap;

		m_platforms.push_back(p);
	}

	m_highestBrokenPlatformPosition = m_highestPlatformPosition;

	m_backgrounds.first.setPosition(0, 0);
	m_backgrounds.second.setPosition(0, SCREEN_HEIGHT * -1.0);

	m_view.setSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	m_view.setCenter(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);

	m_view.move(0, SCREEN_HEIGHT / 2 * -1.0);

	m_feather.setPosition(1000, 1000);
	m_trampoline.setPosition(1000, 1000);
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

	for (int i = 0; i < m_brokenPlatforms.size(); i++)
	{
		if (player.getPosition().y < m_brokenPlatforms[i]->getPlatform().getPosition().y - SCREEN_HEIGHT / 2)
		{
			delete m_brokenPlatforms[i];
			m_brokenPlatforms.erase(m_brokenPlatforms.begin() + i);
			m_brokenPlatformIsFalling.erase(m_brokenPlatformIsFalling.begin() + i);
		}
	}

	createPlatforms(player);

	moveBrokenPlatformDown();

}

void World::moveBrokenPlatformDown()
{
	for (int i = 0; i < m_brokenPlatformIsFalling.size(); i++)
	{
		if (m_brokenPlatformIsFalling[i])
		{
			m_brokenPlatforms[i]->getPlatform().setTextureRect(m_brokenPlatformDownRect);
			m_brokenPlatforms[i]->getPlatform().setPosition(m_brokenPlatforms[i]->getPlatform().getPosition().x, m_brokenPlatforms[i]->getPlatform().getPosition().y + 5);
		}
			
	}
}

void World::createPlatforms(sf::Sprite player)
{
	m_platformGap = rand() % 100 + 100;

	// Create normal platforms
	if (player.getPosition().y - SCREEN_HEIGHT / 2 < m_highestPlatformPosition)
	{
		Platform* p = new Platform;
		p->getPlatform().setTexture(m_tiles);
		p->getPlatform().setTextureRect(m_platformRect);

		float x = rand() % (SCREEN_WIDTH - p->getPlatform().getTextureRect().width);
		p->setup(sf::Vector2f(x, m_highestPlatformPosition - m_platformGap));

		m_highestPlatformPosition = m_highestPlatformPosition - m_platformGap;

		m_platforms.push_back(p);

		// Move feather to new platform
		int offset = 10;
		if (m_feather.getPosition().y - SCREEN_HEIGHT > player.getPosition().y)
		{
			m_feather.setPosition(p->getPlatform().getPosition().x + offset, p->getPlatform().getPosition().y - offset);
			m_feather.setTextureRect(m_featherDefaultRect);
		}
		// Move trampoline to new platofrm
		else if (m_trampoline.getPosition().y - SCREEN_HEIGHT * m_trampolineSpawnRate > player.getPosition().y)
		{
			m_trampoline.setPosition(p->getPlatform().getPosition().x + offset, p->getPlatform().getPosition().y - offset);
			m_trampoline.setTextureRect(m_trampolineDefaultRect);
		}
	}

	// Create broken platforms
	if (player.getPosition().y - SCREEN_HEIGHT / 2 < m_highestBrokenPlatformPosition)
	{
		Platform* p = new Platform;
		p->getPlatform().setTexture(m_tiles);
		p->getPlatform().setTextureRect(m_brokenPlatformRect);

		float x = rand() % (SCREEN_WIDTH - p->getPlatform().getTextureRect().width);
		p->setup(sf::Vector2f(x, m_highestPlatformPosition));

		for (int i = 0; i < m_platforms.size(); i++)
		{
			if (m_platforms[i]->getPlatform().getGlobalBounds().intersects(p->getPlatform().getGlobalBounds()))
			{
				delete p;
				return;
			}
		}

		m_highestBrokenPlatformPosition = m_highestBrokenPlatformPosition - SCREEN_HEIGHT;

		m_brokenPlatformIsFalling.push_back(false);
		m_brokenPlatforms.push_back(p);
	}
}

void World::setFeatherTexture()
{
	m_feather.setPosition(m_feather.getPosition().x, m_feather.getPosition().y - (m_featherJumpedRect.height - m_featherDefaultRect.height));
	m_feather.setTextureRect(m_featherJumpedRect);
}

void World::setTrampolineTexture()
{
	m_trampoline.setPosition(m_trampoline.getPosition().x, m_trampoline.getPosition().y - (m_trampolineJumpedRect.height - m_trampolineDefaultRect.height));
	m_trampoline.setTextureRect(m_trampolineJumpedRect);
}