#include "../include/Sound.h"

bool Sound::loadAssets()
{
	if (!m_jumpBuffer.loadFromFile("assets/sounds/jump.wav") || !m_breakBuffer.loadFromFile("assets/sounds/break.wav") || !m_shootBuffer1.loadFromFile("assets/sounds/shoot1.wav") || 
		!m_shootBuffer2.loadFromFile("assets/sounds/shoot2.wav") || !m_featherBuffer.loadFromFile("assets/sounds/feather.wav"))
		return false;

	return true;
}

void Sound::setup()
{
	m_jump.setBuffer(m_jumpBuffer);
	m_jump.setVolume(m_volume);

	m_break.setBuffer(m_breakBuffer);
	m_break.setVolume(m_volume);

	m_shoot.setBuffer(m_shootBuffer1);
	m_shoot.setVolume(m_volume);

	m_feather.setBuffer(m_featherBuffer);
	m_feather.setVolume(m_volume);
}

void Sound::updateVolume(int volume)
{
	m_volume = volume;

	m_jump.setVolume(m_volume);
	m_break.setVolume(m_volume);
	m_shoot.setVolume(m_volume);
	m_feather.setVolume(m_volume);
}

void Sound::playJumpSound()
{
	m_jump.play();
}

void Sound::playBreakSound()
{
	m_break.play();
}

void Sound::playShootSound()
{
	int r = rand() % 2;

	switch (r)
	{
	case 0:
		m_shoot.setBuffer(m_shootBuffer1);
		break;
	case 1:
		m_shoot.setBuffer(m_shootBuffer2);
		break;
	}

	m_shoot.play();
}

void Sound::playerFeatherSound()
{
	m_feather.play();
}