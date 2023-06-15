#include "../include/Player.h"

bool Player::loadAssets()
{
	if (!m_playerTextureUp.loadFromFile("assets/textures/blue-lik-puca.png") || !m_playerTextureLeft.loadFromFile("assets/textures/blue-lik-left.png") ||
		!m_playerTextureRight.loadFromFile("assets/textures/blue-lik-right.png"))
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

void Player::update()
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
		m_player.setTexture(m_playerTextureLeft);
	}
		
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
	{
		m_player.setPosition(m_player.getPosition().x + velocity, m_player.getPosition().y);
		m_player.setTexture(m_playerTextureRight);
	}
		
}