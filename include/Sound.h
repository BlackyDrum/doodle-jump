#ifndef _SOUND_H_
#define _SOUND_H_

#include "Globals.h"

class Sound
{
public:
	Sound(int volume)
		: m_volume{ volume } {}

	bool loadAssets();

	void setup();

	void updateVolume(int);

	void playJumpSound();

	void playBreakSound();

	void playShootSound();

	void playerFeatherSound();

	void playLoseSound();

	void playTrampolineSound();
private:
	sf::SoundBuffer m_jumpBuffer;
	sf::Sound m_jump;

	sf::SoundBuffer m_breakBuffer;
	sf::Sound m_break;

	sf::SoundBuffer m_shootBuffer1, m_shootBuffer2;
	sf::Sound m_shoot;

	sf::SoundBuffer m_featherBuffer;
	sf::Sound m_feather;

	sf::SoundBuffer m_lostBuffer;
	sf::Sound m_lost;

	sf::SoundBuffer m_trampolineBuffer;
	sf::Sound m_trampoline;

	int m_volume;
};

#endif