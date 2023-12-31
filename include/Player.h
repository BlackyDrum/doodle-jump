#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "Globals.h"

class Player
{
public:
	Player(float velocityDown, float velocityUp, float projectileSpeed) :
		m_isFalling{ false }, m_isJumping{ true }, c_velocityDown{ velocityDown }, m_velocityDown{ velocityDown }, m_projectileSpeed{ projectileSpeed }, 
		c_velocityUp{ velocityUp }, m_velocityUp{ velocityUp }, m_highestPosition{ 0 }, m_isShooting{ false }, m_projectileFireSpeed{ 0.25 },
		m_isLookingLeft{ true } {}

	~Player();

	void setup(sf::Vector2f);

	bool loadAssets();

	void update(sf::View);

	bool jump(float);

	void gravity(float);

	void move(float);

	bool shoot();

	bool checkLose(sf::View);

	sf::Sprite& getPlayer() { return m_player; }
	sf::RectangleShape getBoundingBox() const { return m_boundingBox; }
	std::vector<sf::Sprite*> getProjectiles() const { return m_projectiles; }
	bool getIsFalling() const { return m_isFalling; }
	bool getIsJumping() const { return m_isJumping; }
	float getVelocityUp() const { return m_velocityUp; }
	float getHighestPosition() const { return m_highestPosition; }

	void setIsFalling(bool falling) { m_isFalling = falling; }
	void setIsJumping(bool jumping) { m_isJumping = jumping; }
	void setVelocityUp(float velocity) { m_velocityUp = velocity; }
	void setJumpForce(float force) { c_velocityUp = force; }
	void setProjectileFireSpeed(float speed) { m_projectileFireSpeed = speed; }
private:
	sf::Texture m_playerTextureUp, m_playerTextureLeft, m_playerTextureRight, m_projectileTexture;
	sf::Sprite m_player;

	sf::RectangleShape m_boundingBox;

	sf::Clock m_projectileSpeedClock;

	std::vector<sf::Sprite*> m_projectiles;

	bool m_isFalling, m_isJumping, m_isShooting, m_isLookingLeft;

	float c_velocityDown, m_velocityDown, c_velocityUp, m_velocityUp;

	float m_highestPosition;

	float m_projectileFireSpeed, m_projectileSpeed;
};

#endif