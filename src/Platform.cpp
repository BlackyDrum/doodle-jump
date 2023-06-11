#include "../include/Platform.h"

bool Platform::loadAssets()
{
	if (!m_platformTexture.loadFromFile("assets/textures/game-tiles.png"))
		return false;

	m_platform.setTexture(m_platformTexture);
	m_platform.setTextureRect(sf::IntRect(0, 0, 58, 16));

	return true;
}

void Platform::setup(b2World* world, sf::Vector2f position)
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	bodyDef.position.Set(position.x, position.y);
	m_body = world->CreateBody(&bodyDef);

	b2PolygonShape polygonShape;
	polygonShape.SetAsBox(m_platform.getTextureRect().width / 8, m_platform.getTextureRect().height / 8);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &polygonShape;
	fixtureDef.friction = 0;
	fixtureDef.restitution = 0.0f;

	m_body->CreateFixture(&fixtureDef);

	m_platform.setOrigin(m_platform.getTextureRect().width /2 , m_platform.getTextureRect().height / 2);
	m_platform.setPosition(position);
}