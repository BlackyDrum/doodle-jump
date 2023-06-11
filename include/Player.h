#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "Globals.h"

class Player
{
public:
	void setup(b2World*, sf::Vector2f);

	bool loadAssets();

	void update();

	void jump(float);

	void move(float);

	sf::Sprite getPlayer() const { return m_player; }
	b2Body* getBody() { return m_body; }
private:
	sf::Texture m_playerTexture;
	sf::Sprite m_player;

	b2Body* m_body;
};

#endif