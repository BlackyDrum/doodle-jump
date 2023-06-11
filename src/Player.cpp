#include "../include/Player.h"

bool Player::loadAssets()
{
	if (!m_playerTexture.loadFromFile("assets/textures/blue-lik-puca.png"))
		return false;

	m_player.setTexture(m_playerTexture);

	return true;
}

void Player::setup(b2World* world, sf::Vector2f position)
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(position.x, position.y);
	bodyDef.fixedRotation = true;
	m_body = world->CreateBody(&bodyDef);

	b2PolygonShape polygonShape;
	polygonShape.SetAsBox(m_playerTexture.getSize().x / 2, m_playerTexture.getSize().y / 2);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &polygonShape;
	fixtureDef.density = 1.0;
	fixtureDef.friction = 0.5;
	fixtureDef.restitution = 0.0;

	m_body->CreateFixture(&fixtureDef);
	m_body->SetLinearDamping(0.02);

	m_player.setOrigin(m_playerTexture.getSize().x / 2, m_playerTexture.getSize().y / 2);
	m_player.setPosition(position);
}

void Player::update()
{
	b2Vec2 position = m_body->GetPosition();
	m_player.setPosition(position.x, position.y);
	m_player.setRotation(m_body->GetAngle() * 180 / b2_pi);
}

void Player::jump(float velocity)
{
	m_body->ApplyLinearImpulse(b2Vec2(0,-velocity), m_body->GetWorldCenter(), true);
}

void Player::move(float velocity)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		m_body->ApplyLinearImpulse(b2Vec2(-velocity, 0), m_body->GetWorldCenter(), true);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		m_body->ApplyLinearImpulse(b2Vec2(velocity, 0), m_body->GetWorldCenter(), true);
}