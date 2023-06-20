#include "../include/Player.h"

Player::~Player()
{
	for (auto& p : m_projectiles)
		delete p;
}

bool Player::loadAssets()
{
	if (!m_playerTextureUp.loadFromFile("assets/textures/blue-lik-puca.png") || !m_playerTextureLeft.loadFromFile("assets/textures/blue-lik-left.png") ||
		!m_playerTextureRight.loadFromFile("assets/textures/blue-lik-right.png") || !m_projectileTexture.loadFromFile("assets/textures/projectile-tiles.png"))
		return false;

	m_player.setTexture(m_playerTextureLeft);

	return true;
}

void Player::setup(sf::Vector2f position)
{
	m_player.setPosition(position);

	m_boundingBox.setPosition(position.x, position.y);
	m_boundingBox.setSize(sf::Vector2f(m_player.getTextureRect().width / 2, m_player.getTextureRect().height / 8));
	m_boundingBox.setFillColor(sf::Color::Red);
}

void Player::update(sf::View view)
{
	if (m_velocityUp <= 0)
	{
		m_isFalling = true;
		m_isJumping = false;

		m_velocityUp = c_velocityUp;
		m_velocityDown = 0;
	}

	m_boundingBox.setPosition(m_player.getPosition().x + m_player.getTextureRect().width / 4, m_player.getPosition().y + m_player.getTextureRect().height);

	if (m_player.getPosition().x + m_player.getTextureRect().width <= 0)
		m_player.setPosition(SCREEN_WIDTH, m_player.getPosition().y);
	else if (m_player.getPosition().x > SCREEN_WIDTH)
		m_player.setPosition(-m_player.getTextureRect().width, m_player.getPosition().y);

	// Move and delete projectiles
	for (int i = 0; i < m_projectiles.size(); i++)
	{
		m_projectiles[i]->setPosition(m_projectiles[i]->getPosition().x, m_projectiles[i]->getPosition().y - 20);

		if (m_projectiles[i]->getPosition().y < view.getCenter().y - SCREEN_HEIGHT)
		{
			delete m_projectiles[i];
			m_projectiles.erase(m_projectiles.begin() + i);
		}
			
	}

}

bool Player::jump(float velocity)
{
	if (m_isJumping)
	{
		m_player.setPosition(m_player.getPosition().x, m_player.getPosition().y - m_velocityUp);
		m_velocityUp -= velocity;

		if (m_player.getPosition().y < m_highestPosition)
			m_highestPosition = m_player.getPosition().y;

		return true;
	}

	return false;
}

void Player::gravity(float velocity)
{
	if (m_isFalling)
	{
		m_player.setPosition(m_player.getPosition().x, m_player.getPosition().y + m_velocityDown);
		m_velocityDown += velocity;
	}
}

void Player::move(float velocity)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
	{
		m_player.setPosition(m_player.getPosition().x - velocity, m_player.getPosition().y);
		m_player.setTexture(m_isShooting ? m_playerTextureUp : m_playerTextureLeft);
		m_isLookingLeft = true;
	}
		
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
	{
		m_player.setPosition(m_player.getPosition().x + velocity, m_player.getPosition().y);
		m_player.setTexture(m_isShooting ? m_playerTextureUp : m_playerTextureRight);
		m_isLookingLeft = false;
	}
		
}

bool Player::shoot()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && m_projectileSpeedClock.getElapsedTime().asSeconds() > m_projectileSpeed)
	{
		int offset = 10;

		m_isShooting = true;

		sf::Sprite* p = new sf::Sprite;

		p->setTexture(m_projectileTexture);
		p->setTextureRect(sf::IntRect(0, 0, 12, 12));
		p->setPosition(m_player.getPosition().x + m_player.getTextureRect().width / 2 - offset, m_player.getPosition().y - m_player.getTextureRect().height / 2 + offset);

		m_projectiles.push_back(p);

		m_player.setTexture(m_playerTextureUp);

		m_projectileSpeedClock.restart();

		return true;
	}

	if (m_projectileSpeedClock.getElapsedTime().asSeconds() > 0.25)
	{
		m_isShooting = false;
		m_player.setTexture(m_isLookingLeft ? m_playerTextureLeft : m_playerTextureRight);
	}
		
	return false;
	
}