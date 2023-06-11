#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "Globals.h"

class Player
{
public:
	Player(float velocityDown, float velocityUp) :
		m_isFalling{ true }, m_isJumping{ false }, c_velocityDown{ velocityDown }, m_velocityDown{ velocityDown },
		c_velocityUp{ velocityUp }, m_velocityUp{ velocityUp }, m_highestPosition{ 0 } {}

	void setup(sf::Vector2f);

	bool loadAssets();

	void update();

	bool jump(float);

	void gravity(float);

	void move(float);

	sf::Sprite getPlayer() const { return m_player; }
	sf::RectangleShape getBoundingBox() const { return m_boundingBox; }
	bool getIsFalling() const { return m_isFalling; }
	bool getIsJumping() const { return m_isJumping; }
	float getVelocityUp() const { return m_velocityUp; }
	float getHighestPosition() const { return m_highestPosition; }

	void setIsFalling(bool falling) { m_isFalling = falling; }
	void setIsJumping(bool jumping) { m_isJumping = jumping; }
private:
	sf::Texture m_playerTexture;
	sf::Sprite m_player;

	sf::RectangleShape m_boundingBox;

	bool m_isFalling, m_isJumping;

	float c_velocityDown, m_velocityDown, c_velocityUp, m_velocityUp;

	float m_highestPosition;
};

#endif